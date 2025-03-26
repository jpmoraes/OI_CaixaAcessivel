import os
import requests
from flask import Flask, send_from_directory, jsonify, render_template

# IP do ESP32 para o qual a requisição GET será enviada
ESP32_IP = "172.26.3.80"  # Substitua pelo IP real do ESP32

app = Flask(__name__)

# Serve a página index.html
@app.route('/')
def index():
    return render_template('index.html')

# Serve os arquivos estáticos (CSS e JS)
@app.route('/css/<path:filename>')
def serve_css(filename):
    return send_from_directory(os.path.join('static', 'css'), filename)

@app.route('/js/<path:filename>')
def serve_js(filename):
    return send_from_directory(os.path.join('static', 'js'), filename)

# Ações do ESP32 (turn_on / turn_off)
@app.route('/turn_on')
def turn_on():
    return send_esp32_request('turn_on')

@app.route('/turn_off')
def turn_off():
    return send_esp32_request('turn_off')

def send_esp32_request(action):
    """ Envia a requisição GET para o ESP32 e trata o retorno. """
    try:
        response = requests.get(f'http://{ESP32_IP}/{action}')
        message = response.text
        status_code = response.status_code
    except requests.RequestException as e:
        message = f'Error: {str(e)}'
        status_code = 500

    return jsonify({'message': message}), status_code


if __name__ == '__main__':
    app.run(debug=True, port=8000)
