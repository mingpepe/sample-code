from flask import render_template, Flask, send_from_directory

app = Flask(__name__)

@app.route('/')
def index():
    return render_template('index.html')


@app.route('/video/<string:file_name>')
def stream(file_name):
    video_dir = './video'
    return send_from_directory(directory=video_dir, path=file_name)

if __name__ == '__main__':
    app.run()
