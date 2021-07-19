from flask import Flask 
from werkzeug.routing import Rule
from user_bp import user_bp
from flights_bp import flights_bp
from passengers_bp import passengers_bp
from relationship_bp import relationship_bp
from oauth_bp import oauth_bp

# This disables the requirement to use HTTPS so that you can test locally.
import os 
os.environ['OAUTHLIB_INSECURE_TRANSPORT'] = '1'

app = Flask(__name__)
app.register_blueprint(user_bp)
app.register_blueprint(flights_bp)
app.register_blueprint(passengers_bp)
app.register_blueprint(relationship_bp)
app.register_blueprint(oauth_bp)
app.url_map.add(Rule('/', endpoint='index'))
app.url_map.add(Rule('/oauth', endpoint = 'oauth'))
app.url_map.add(Rule('/users', endpoint = 'users'))
app.url_map.add(Rule('/flights', endpoint = 'flights'))
app.url_map.add(Rule('/flights/<id>', endpoint = 'flights<id>'))
app.url_map.add(Rule('/passengers', endpoint = 'passengers'))
app.url_map.add(Rule('/passengers/<id>', endpoint = 'passengers<id>'))
app.url_map.add(Rule('/flights/<fid>/passengers/<pid>', endpoint = 'relationship'))
app.config['SECRET_KEY'] = "I am very sneaky"


if __name__ == '__main__':
    app.run(host='127.0.0.1', port=8080, debug=True)