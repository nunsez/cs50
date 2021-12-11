CREATE TABLE users (
    id INTEGER,
    username TEXT NOT NULL,
    hash TEXT NOT NULL,
    cash NUMERIC NOT NULL DEFAULT 10000.00,
    PRIMARY KEY(id)
);

CREATE UNIQUE INDEX username ON users (username);

CREATE TABLE companies (
    id INTEGER PRIMARY KEY,
    symbol TEXT UNIQUE NOT NULL,
    name TEXT NOT NULL DEFAULT "",
    price NUMERIC NOT NULL DEFAULT 0.0
);

CREATE UNIQUE INDEX company_id on companies (id);

CREATE TABLE transactions (
    id INTEGER PRIMARY KEY,
    user_id INTEGER,
    company_id INTEGER,
    shares INTEGER NOT NULL,
    price NUMERIC NOT NULL,
    type TEXT NOT NULL,
    created_at TEXT NOT NULL,
    FOREIGN KEY (user_id) REFERENCES users(id),
    FOREIGN KEY (company_id) REFERENCES companies(id)
);

CREATE TABLE portfolio_entries (
    id INTEGER PRIMARY KEY,
    user_id INTEGER,
    company_id INTEGER UNIQUE,
    shares INTEGER DEFAULT 0,
    FOREIGN KEY (user_id) REFERENCES users(id),
    FOREIGN KEY (company_id) REFERENCES companies(id)
);

CREATE UNIQUE INDEX portfolio_entries_company_id on portfolio_entries (company_id);
