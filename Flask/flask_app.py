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


user_schema = UsersSchema()
users_schema = UsersSchema(many=True)


class Shape(db.Model):

    __tablename__ = "shape"
    id = db.Column(db.Integer, primary_key=True)
    fullName = db.Column(db.String(4096))
    machineId = db.Column(db.Integer)
    data = db.Column(db.Integer)


    def __init__(self, full_name, machine_id, data_):
        self.fullName = full_name
        self.machineId = machine_id
        self.data = data_

class ShapesSchema(ma.Schema):
    class Meta:
        fields = ('id' ,'fullName', 'machineId', 'data')

shape_schema = ShapesSchema()
shapes_schema = ShapesSchema(many=True)


class Machine(db.Model):

    __tablename__ = "machine"
    id = db.Column(db.Integer, primary_key=True)
    orderId = db.Column(db.Integer)


    def __init__(self, order_id):
        self.orderId = order_id

class MachineSchema(ma.Schema):
    class Meta:
        fields = ('id' ,'orderId')


machine_schema = MachineSchema()


class Order(db.Model):

    __tablename__ = "order"
    id = db.Column(db.Integer, primary_key=True)
    userId = db.Column(db.Integer)
    shapeId = db.Column(db.Integer)

    def __init__(self, user_id, shape_id):
        self.userId = user_id
        self.shapeId = shape_id

class OrderSchema(ma.Schema):
    class Meta:
        fields = ('id' ,'userId', 'shapeId')


order_schema = OrderSchema()
orders_schema = OrderSchema(many=True)


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


@app.route('/shape/<id>', methods=["GET"])
def get_all_shape(id):
     shape = Shape.query.get(id)
     result = shape_schema.dump(shape)
     return jsonify(result)

@app.route("/shape/post", methods=["POST"])
def add_shape():
    name= request.json["fullName"]
    machine_id= request.json["machineId"]
    data_= request.json["data"]
    new_shape = Shape(name, machine_id, data_)
    db.session.add(new_shape)
    db.session.commit()  # PK increment
    shape = Shape.query.get(new_shape.id)
    return shape_schema.jsonify(shape)


@app.route('/machine/<id>', methods=["GET"])
def get_all_machine(id):
     machine = Machine.query.get(id)
     result = machine_schema.dump(machine)
     return jsonify(result)

@app.route("/machine/post", methods=["POST"])
def add_machine():
    order_id= request.json["orderId"]
    new_machine = Users(order_id)
    db.session.add(new_machine)
    db.session.commit()  # PK increment
    machine = Machine.query.get(new_machine.id)
    return machine_schema.jsonify(machine)

@app.route('/order/<id>', methods=["GET"])
def get_all_order(id):
    order = Order.query.get(id)
    result = order_schema.dump(order)
    return jsonify(result)

@app.route("/order/post", methods=["POST"])
def add_order():
    user_id= request.json["userId"]
    shape_id= request.json["shapeId"]
    new_order = Order(user_id, shape_id)
    db.session.add(new_order)
    db.session.commit()  # PK increment
    order = Order.query.get(new_order.id)
    return order_schema.jsonify(order)