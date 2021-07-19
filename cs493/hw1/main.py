import datetime
from flask import Flask, render_template, request
from google.cloud import datastore

datastore_client = datastore.Client()

app = Flask(__name__)

def store_time(dt):
    entity = datastore.Entity(key=datastore_client.key('visit'))
    entity.update({
        'timestamp': dt
    })

    datastore_client.put(entity)


def fetch_times(limit):
    query = datastore_client.query(kind='visit')
    query.order = ['-timestamp']

    times = query.fetch(limit=limit)

    return times


@app.route('/')
def index():
    # Store the current access time in Datastore.
    store_time(datetime.datetime.now())
    # Fetch the most recent 10 access times from Datastore.
    times = fetch_times(10)
    
    return render_template('index.html', times=times)
    
@app.route('/result', methods=['POST'])
def result():
    # Store the current access time in Datastore.
    store_time(datetime.datetime.now())
    # Fetch the most recent 10 access times from Datastore.
    times = fetch_times(10)
    
    first = request.form['firstName']
    last = request.form['lastName']
    res = first + " " + last
    
    return render_template('result.html', name=res, times=times)
