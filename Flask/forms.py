from flask_wtf import Form
from wtforms import TextField, IntegerField, TextAreaField, SubmitField, RadioField, SelectField, DateField, PasswordField, BooleanField
from wtforms import validators, ValidationError



class AddUserForm(Form):
   name = TextField("Imie nazwisko",[validators.Required("Wprowadz dane")],default="dane")
   submit = SubmitField("Zmien USER")
   select = SelectField('Produce',coerce=int,validate_choice=False)