from flask import Flask, redirect, render_template, request, jsonify, abort, flash
from flask_sqlalchemy import SQLAlchemy
from forms import AddUserForm
from flask_marshmallow import Marshmallow



app = Flask(__name__)
app.secret_key = 'development key'

SQLALCHEMY_DATABASE_URI = "mysql+mysqlconnector://{username}:{password}@{hostname}/{databasename}".format(
    username="KrzysztofSZCZ",
    password="alamakota",
    hostname="KrzysztofSZCZ.mysql.pythonanywhere-services.com",
    databasename="KrzysztofSZCZ$Laserv2",
)
app.config["SQLALCHEMY_DATABASE_URI"] = SQLALCHEMY_DATABASE_URI
app.config["SQLALCHEMY_POOL_RECYCLE"] = 299 # connection timeouts
app.config["SQLALCHEMY_TRACK_MODIFICATIONS"] = False # no warning disruptions


db = SQLAlchemy(app)
ma = Marshmallow(app)

class Users(db.Model):

    __tablename__ = "users"
    id = db.Column(db.Integer, primary_key=True)
    fullName = db.Column(db.String(4096))


    def __init__(self, full_name):
        self.fullName = full_name

class UsersSchema(ma.Schema):
    class Meta:
        fields = ('id' ,'fullName')


@app.route('/z')
def hello_world():
    return 'Pozdrawiamy!!!'

user_schema = UsersSchema()
users_schema = UsersSchema(many=True)


@app.route('/users', methods=["GET"])
def get_all_users():
     user_many = Users.query.all()
     result = users_schema.dump(user_many)
     return jsonify(result)

@app.route('/user/<id>', methods=["GET"])
def get_all_user(id):
     user = Users.query.get(id)
     result = user_schema.dump(user)
     return jsonify(result)

@app.route("/users/post", methods=["POST"])
def add_user():
    name= request.json["fullName"]
    new_user = Users(name)
    db.session.add(new_user)
    db.session.commit()  # PK increment
    user = Users.query.get(new_user.id)
    return user_schema.jsonify(user)

@app.route("/web/users", methods=["GET"])
def get_users_nasz():
    all_users = Users.query.order_by(Users.fullName).all()
    result = users_schema.dump(all_users)
    return render_template('laseripz.html', title = 'Strona bazy danych lasera IPZ', users=result)

@app.route("/web/post", methods=["GET", "POST"])
def getUserNaszDodaj():
    form = AddUserForm()
    if request.method == 'POST':
            name= form.name.data
            new_user = Users(name)
            db.session.add(new_user)
            db.session.commit()

    user = Users.query.all()
    result = users_schema.dump(user)
    flash('Dodano uzytkownika!!!')
    return render_template('wpiszdane.html',title='Baza danych lasera',  users= result, form=form)