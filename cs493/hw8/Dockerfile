FROM python:3.7
WORKDIR /usr/src/app
COPY requirements.txt ./
RUN pip install -r requirements.txt 
COPY . .
ENV GOOGLE_APPLICATION_CREDENTIALS='./hw8-hawkesc-cs493.json'
ENV PORT=8000
EXPOSE ${PORT}
CMD [ "python", "main.py" ]
