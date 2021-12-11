import os
import requests
import urllib.parse

from flask import redirect, render_template, request, session
from functools import wraps


def apology(message, code=400):
    """Render message as an apology to user."""
    def escape(s):
        """
        Escape special characters.

        https://github.com/jacebrowning/memegen#special-characters
        """
        for old, new in [("-", "--"), (" ", "-"), ("_", "__"), ("?", "~q"),
                         ("%", "~p"), ("#", "~h"), ("/", "~s"), ("\"", "''")]:
            s = s.replace(old, new)
        return s
    return render_template("apology.html", top=code, bottom=escape(message)), code


def login_required(f):
    """
    Decorate routes to require login.

    https://flask.palletsprojects.com/en/1.1.x/patterns/viewdecorators/
    """
    @wraps(f)
    def decorated_function(*args, **kwargs):
        if session.get("user_id") is None:
            return redirect("/login")
        return f(*args, **kwargs)
    return decorated_function


def lookup(symbol):
    """Look up quote for symbol."""

    # Contact API
    try:
        api_key = os.environ.get("API_KEY")
        url = f"https://cloud.iexapis.com/stable/stock/{urllib.parse.quote_plus(symbol)}/quote?token={api_key}"
        response = requests.get(url)
        response.raise_for_status()
    except requests.RequestException:
        return None

    # Parse response
    try:
        quote = response.json()
        return {
            "name": quote["companyName"],
            "price": float(quote["latestPrice"]),
            "symbol": quote["symbol"]
        }
    except (KeyError, TypeError, ValueError):
        return None


def usd(value):
    """Format value as USD."""
    return f"${value:,.2f}"

def validate_register_form(username, password, confirmation):
    blank = "can't be blank."
    not_matched = "passwords don't match"
    errors = {}

    if not username:
        errors['username'] = blank

    if not password:
        errors['password'] = blank

    if password != confirmation:
        errors['password'] = not_matched

    return errors


def validate_buy_form(symbol, shares):
    blank = "can't be blank."
    positive = 'must be positive.'
    not_number = 'must be a number'
    errors = {}

    if not symbol:
        errors['symbol'] = blank

    try:
        shares_int = int(shares)
    except:
        errors['shares'] = not_number
    else:
        if shares_int <= 0:
            errors['shares'] = positive

    if not shares:
        errors['shares'] = blank

    return errors


def validate_cash(cash):
    blank = "can't be blank."
    not_number = 'not a number.'
    positive = 'must be positive.'
    errors = {}

    if not cash:
        errors['cash'] = blank

        return errors

    try:
        cash_int = int(cash)
    except:
        errors['cash'] = not_number
    else:
        if cash_int <= 0:
            errors['cash'] = positive

    return errors
