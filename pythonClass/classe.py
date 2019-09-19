import serial


class Arm:

    def __init__(self, port):
        self.port = port
    

    def begin(self):
        self.conexao = serial.Serial(self.port, 9600) # Configuração da conexão

    def send(self, valor):
        self.valor = valor
        self.conexao.write(self.valor)

