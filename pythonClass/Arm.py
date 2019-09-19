import serial


class Arm:

    def __init__(self, port):
        self.port = port

    def begin(self):
        self.conexao = serial.Serial(self.port, 9600)  # Configuração da conexão

    def send(self, valor):
        self.conexao.write(valor)

    def home(self):
        self.conexao.write(b'G28')

    def junta1(self, angulo):
        comand = b'G1 A'
        self.conexao.write(self.comand, self.angulo)

    def junta2(self, angulo3):
        self.conexao.write(self.comand, self.angulo)

    def junta3(self, angulo3):
        self.conexao.write(b'G1 C', self.angulo3)

    def sendMove(self, _value,  _joint):
        msg = "G1 "
        joint = chr( 65 + _joint)
        msg += joint
        msg += str(_value)
        msg += ';'
        print(msg)
        send(msg)
        # TODO: Adicionar while travante


