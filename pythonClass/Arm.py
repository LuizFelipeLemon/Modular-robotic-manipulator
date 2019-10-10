import serial
import numpy as np



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


    def read(self, size):
        self.conexao.read(size)


    def sendMsgNoWait(self, _msg)
        read(4)

        _msg += ";"
        print(_msg)
        send(_msg)


    def sendMsg(self, _msg)
        read(4)

        _msg += ";"
        print(_msg)
        send(_msg)

        read(1)


    def sendMoveNoWait(self, _value,  _joint):
        msg = "G1 "
        joint = chr( 65 + _joint)
        msg += joint
        msg += str(_value)
        msg += ';'
        print(msg)
        send(msg)


    def sendMove(self, _value,  _joint):
        msg = "G1 "
        joint = chr( 65 + _joint)
        msg += joint
        msg += str(_value)
        msg += ';'
        print(msg)
        send(msg)

        read(2)


    def sendMoveMultiNoWait(value, joint,size):
        read(4)

        msg = "G1 "
        for i in range(0,size):
            joint = chr( 65 + joint[i])
            msg += joint
            msg += str(value[i])
            msg += ' '

        msg+=";"
        print(msg)
        send(msg)


    def sendMoveMulti(value, joint,size):
        read(4)

        msg = "G1 "
        for i in range(0,size):
            joint = chr( 65 + joint[i])
            msg += joint
            msg += str(value[i])
            msg += ' '

        msg+=";"
        print(msg)
        send(msg)

        read(2)


    def multiMatrix(self, A, B, R)
        R = np.zeros((4,4), dtype=np.double)
        #por padrão o tipo é float64
        R = np.dot(A,B)

