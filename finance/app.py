import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    user_id = session["user_id"]
    stocks = db.execute("SELECT name, price, shares, SUM(shares) AS total FROM transactions WHERE user_id = ? GROUP BY name", user_id)
    cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]["cash"]

    grand_total = 10000
    image = "https://i.imgur.com/CsCgN7Ll.png"

    return render_template("index.html", stocks=stocks, cash=cash, grand_total=grand_total, usd=usd, image=image)

    #return apology("TODO")


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("must provide symbol", 400)
        stocks = lookup(symbol)
        if stocks is None:
            return apology("invalid symbol", 400)
        try:
            shares = int(request.form.get("shares"))
        except:
            return apology("number of shares must be an integer", 400)
        if shares <= 0:
            return apology("number of shares must be a positive integer", 400)
        user_id = session["user_id"]
        stock_name = stocks["name"]
        stock_price = stocks["price"]
        total_price = stock_price * shares
        cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]["cash"]
        if total_price > cash:
            return apology("you do not have enough cash for this purchase", 400)

        transaction_type = "Bought"

        db.execute("INSERT INTO transactions (user_id, name, shares, price, type) VALUES(?, ?, ?, ?, ?)", user_id, stock_name, shares, stock_price, transaction_type)
        cash_left = cash - total_price
        db.execute("UPDATE users SET cash = ? WHERE id = ?", cash_left, user_id)

        return redirect("/")

    else:
        return render_template("buy.html")

@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    return apology("TODO")


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("must provide symbol", 400)
        stocks = lookup(symbol)
        if stocks is None:
            return apology("not a valid stock", 400)

        return render_template("/quoted.html", stocks=stocks, usd=usd)

    else:
         return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        username = request.form.get("username")
        if not username:
            return apology("must provide username", 400)
        # Ensure username was submitted
        if not username:
            return apology("must provide username", 400)
        elif username == db.execute("SELECT username FROM users WHERE username = username"):
            return apology("username already exists", 400)
        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)
        elif len(request.form.get("password")) < 8:
            return apology("password should be at least 8 characters long", 400)
        # Ensure password was submitted
        elif not request.form.get("confirmation"):
            return apology("must confirm password", 403)
        # Ensure password matches
        elif request.form.get("password") != request.form.get("confirmation"):
            return apology("your password does not match", 400)

        password = generate_password_hash(request.form.get("password"))

        try:
            new_user = db.execute("INSERT INTO users (username, hash) VALUES(?, ?)", username, password)
            if new_user is None:
                return apology("Registration error", 400)
            session["user_id"] = new_user
            return redirect("/")

        except:
            return apology("username already exists", 400)

        # Redirect user to home page
        return redirect("/")

    else:
            return render_template("register.html")




@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    return render_template("sell.html")
