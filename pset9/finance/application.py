import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd, validate_register_form, validate_buy_form, validate_cash

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config['TEMPLATES_AUTO_RELOAD'] = True


# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers['Cache-Control'] = 'no-cache, no-store, must-revalidate'
    response.headers['Expires'] = 0
    response.headers['Pragma'] = 'no-cache'
    return response


# Custom filter
app.jinja_env.filters['usd'] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config['SESSION_FILE_DIR'] = mkdtemp()
app.config['SESSION_PERMANENT'] = False
app.config['SESSION_TYPE'] = 'filesystem'
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL('sqlite:///finance.db')

# Make sure API key is set
if not os.environ.get('API_KEY'):
    raise RuntimeError('API_KEY not set')


@app.route('/')
@login_required
def index():
    """Show portfolio of stocks"""
    user_id = session.get('user_id')

    try:
        summary = db.execute(
            "SELECT symbol, name, price, shares \
            FROM portfolio_entries \
            JOIN companies \
                ON portfolio_entries.company_id = companies.id \
            WHERE portfolio_entries.user_id = ? AND portfolio_entries.shares != 0 \
            GROUP BY symbol",
            user_id
        )

        money_spend = 0

        for company in summary:
            total_by_company = company['price'] * company['shares']
            money_spend += total_by_company

        user_cash = db.execute('SELECT cash FROM users WHERE id = ? LIMIT 1', user_id)
        user_cash = user_cash[0]['cash']
    except:
        return render_template('index.html', error='Something went wrong. Try again later.')

    return render_template('index.html', summary=summary, user_cash=user_cash, money_spend=money_spend)


@app.route('/buy', methods=['GET', 'POST'])
@login_required
def buy():
    """Buy shares of stock"""

    if request.method == 'GET':
        return render_template('buy.html')

    if request.method == 'POST':
        user_id = session.get('user_id')
        symbol = request.form.get('symbol')
        shares = request.form.get('shares')
        data = { 'symbol': symbol, 'shares': shares }

        errors = validate_buy_form(symbol, shares)

        if errors:
            return render_template('buy.html', data=data, errors=errors)

        user_cash = get_user_cash(user_id)

        if not user_cash:
            cash_error = 'Something went wrong. Try again later.'

            return render_template('buy.html', data=data, errors={ 'cash': cash_error })

        company = lookup(symbol)
        update_company(company)

        if not company:
            quote_error = 'not found.'

            return render_template('buy.html', data=data, errors={ 'symbol': quote_error })

        price = company['price']
        total_price = price * int(shares)

        if user_cash < total_price:
            shares_error = 'Not enough money to buy that many shares.'

            return render_template('buy.html', data=data, errors={ 'message': shares_error })

        if not buy_shares(user_id, company['symbol'], price, shares):
            cash_error = 'Something went wrong. Try again later.'

            return render_template('buy.html', data=data, errors={ 'message': cash_error })

        return redirect('/')


@app.route('/history')
@login_required
def history():
    """Show history of transactions"""

    user_id = session.get('user_id')

    try:
        transactions = db.execute(
            "SELECT companies.symbol, transactions.shares, transactions.price, transactions.type, transactions.created_at \
            FROM transactions \
            JOIN companies \
                ON transactions.company_id = companies.id \
            WHERE transactions.user_id = ? ORDER BY created_at DESC",
            user_id
        )
    except:
        return render_template('history.html', error='Something went wrong. Try again later.')

    return render_template('history.html', transactions=transactions)


@app.route('/login', methods=['GET', 'POST'])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == 'POST':

        # Ensure username was submitted
        if not request.form.get('username'):
            return apology('must provide username', 403)

        # Ensure password was submitted
        elif not request.form.get('password'):
            return apology('must provide password', 403)

        # Query database for username
        rows = db.execute('SELECT * FROM users WHERE username = ?', request.form.get('username'))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]['hash'], request.form.get('password')):
            return apology('invalid username and/or password', 403)

        # Remember which user has logged in
        session['user_id'] = rows[0]['id']

        # Redirect user to home page
        return redirect('/')

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template('login.html')


@app.route('/logout')
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect('/')


@app.route('/quote', methods=['GET', 'POST'])
@login_required
def quote():
    """Get stock quote."""
    if request.method == 'GET':
        return render_template('quote.html')

    if request.method == 'POST':
        symbol = request.form.get('symbol')
        company = lookup(symbol)
        update_company(company)

        if not company:
            message = 'not found.'
            return render_template('quote.html', message=message)

        return render_template('quoted.html', company=company)


@app.route('/register', methods=['GET', 'POST'])
def register():
    """Register user"""

    if request.method == 'GET':
        return render_template('register.html', )

    if request.method == 'POST':
        username = request.form.get('username')
        password = request.form.get('password')
        confirmation = request.form.get('confirmation')
        user = { 'username': username }

        errors = validate_register_form(username, password, confirmation)

        if errors:
            return render_template('register.html', errors=errors, user=user)

        try:
            current_user = db.execute('SELECT id FROM users WHERE username = ?', username)
        except:
            check_error = 'Something went wrong. Try again later.'

            return render_template('register.html', user=user, errors={ 'register': check_error })

        if current_user:
            exist = 'already exist.'

            return render_template('register.html', user=user, errors={ 'username': exist })

        user_id = register_user(username, password)

        if not user_id:
            register_error = 'Something went wrong. Try again later.'

            return render_template('register.html', user=user, errors={ 'register': register_error })
        else:
            session['user_id'] = user_id

        return redirect('/')


@app.route('/sell', methods=['GET', 'POST'])
@login_required
def sell():
    """Sell shares of stock"""

    user_id = session.get('user_id')

    try:
        symbols_list = db.execute(
            "SELECT symbol FROM companies WHERE id IN (SELECT company_id FROM portfolio_entries WHERE user_id = ?)",
            user_id
        )

        symbols_list = map(lambda o: o['symbol'], symbols_list)
    except:
        sell_error = 'Something went wrong. Try again later.'

        return render_template('sell.html', errors={ message: sell_error })

    if request.method == 'GET':
        return render_template('sell.html', symbols_list=symbols_list)

    if request.method == 'POST':
        symbol = request.form.get('symbol')
        shares = request.form.get('shares')

        errors = validate_sell_form(user_id, symbol, shares)

        if errors:
            return render_template('sell.html', symbols_list=symbols_list, errors=errors)

        company = lookup(symbol)
        update_company(company)

        if not sell_shares(user_id, symbol, shares):
            sell_error = 'Something went wrong. Try again later.'

            return render_template('sell.html', symbols_list=symbols_list, errors={ message: sell_error })

        return redirect('/')


@app.route('/add-cash', methods=['GET', 'POST'])
@login_required
def cash():
    """Add Cash."""

    if request.method == 'GET':
        return render_template('cash.html')

    if request.method == 'POST':
        user_id = session.get('user_id')
        cash = request.form.get('cash')

        errors = validate_cash(cash)

        if errors:
            return render_template('cash.html', errors=errors)

        if not add_cash(user_id, cash):
            cash_error = 'Something went wrong. Try again later.'

            return render_template('cash.html', errors={ 'cash': cash_error })

        return redirect('/')


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)

def register_user(username, password):
    password_hash = generate_password_hash(password)

    try:
        user_id = db.execute(
            'INSERT INTO users (username, hash) VALUES (?, ?)',
            username, password_hash
        )
    except:
        return False
    else:
        return user_id

def get_user_cash(user_id):
    try:
        user_cash = db.execute('SELECT cash FROM users WHERE id = ?', user_id)
    except:
        return None
    else:
        return user_cash[0]['cash']


def buy_shares(user_id, symbol, price, shares):
    total_price = float(price) * int(shares)

    try:
        company_id = db.execute("SELECT id FROM companies WHERE symbol = ?", symbol)
        company_id = company_id[0]['id']

        db.execute(
            "INSERT INTO transactions (user_id, company_id, shares, price, type, created_at) \
            VALUES (?, ?, ?, ?, 'buy', datetime('now'))",
            user_id, company_id, shares, price
        )
        db.execute(
            "INSERT INTO portfolio_entries (user_id, company_id, shares) \
            VALUES (?, ?, ?) \
            ON CONFLICT (company_id) \
            DO UPDATE SET shares = shares + ?",
            user_id, company_id, shares, shares
        )
        db.execute("UPDATE users SET cash = cash - ? WHERE id = ?", total_price, user_id)
    except:
        return False
    else:
        return True


def sell_shares(user_id, symbol, shares):
    try:
        company_id = db.execute("SELECT id FROM companies WHERE symbol = ?", symbol)
        company_id = company_id[0]['id']

        price = db.execute("SELECT price FROM companies WHERE id = ?", company_id)
        price = price[0]['price']
        total_price = price * int(shares)

        db.execute(
            "INSERT INTO transactions (user_id, company_id, shares, price, type, created_at) \
            VALUES (?, ?, ?, ?, 'sell', datetime('now'))",
            user_id, company_id, shares, price
        )
        db.execute(
            "INSERT INTO portfolio_entries (user_id, company_id, shares) \
            VALUES (?, ?, ?) \
            ON CONFLICT (company_id) \
            DO UPDATE SET shares = shares - ?",
            user_id, company_id, shares, shares
        )
        db.execute("UPDATE users SET cash = cash + ? WHERE id = ?", total_price, user_id)
    except:
        return False
    else:
        return True


def update_company(company):
    if not company:
        return False

    try:
        db.execute(
            "INSERT INTO companies (symbol, name, price) VALUES (?, ?, ?)",
            company['symbol'], company['name'], company['price']
        )
    except:
        return False
    else:
        return True


def add_cash(user_id, cash):
    cash_int = int(cash)

    try:
        db.execute('UPDATE users SET cash = cash + ? WHERE id = ?', cash, user_id)
    except:
        return False
    else:
        return True


def validate_sell_form(user_id, symbol, shares):
    blank = 'can\'t be blank.'
    positive = 'must be positive.'
    not_number = 'must be a number'
    errors = {}

    try:
        shares_int = int(shares)
    except:
        errors['shares'] = not_number
    else:
        if shares_int <= 0:
            errors['shares'] = positive

    if not shares:
        errors['shares'] = blank

    if not symbol:
        errors['symbol'] = blank

        return errors

    try:
        symbols_list = db.execute(
            "SELECT symbol FROM companies WHERE id IN (SELECT company_id FROM portfolio_entries WHERE user_id = ?)",
            user_id
        )

        symbols_list = map(lambda o: o['symbol'], symbols_list)

        if symbol not in symbols_list:
            errors['symbol'] = 'not in portfolio.'

            return errors
    except:
        errors['message'] = 'Something went wrong. Try again later.'

        return errors

    try:
        user_shares = db.execute(
            "SELECT shares FROM portfolio_entries WHERE user_id = ? AND company_id IN (SELECT id FROM companies WHERE symbol = ?)",
            user_id, symbol
        )
        user_shares = user_shares[0]['shares']

        if user_shares < shares_int:
            errors['shares'] = 'don\'t have so much.'
    except:
        errors['message'] = 'Something went wrong. Try again later.'

    return errors
