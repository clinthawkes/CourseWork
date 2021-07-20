from app import app
from flaskext.mysql import MySQL

mysql = MySQL()
 
# MySQL configurations
app.config['MYSQL_DATABASE_USER'] = 'b2ea584bffbae2'
app.config['MYSQL_DATABASE_PASSWORD'] = '0d24a66d'
app.config['MYSQL_DATABASE_DB'] = 'heroku_7236e234ae5516f'
app.config['MYSQL_DATABASE_HOST'] = 'us-cdbr-iron-east-04.cleardb.net'
mysql.init_app(app)