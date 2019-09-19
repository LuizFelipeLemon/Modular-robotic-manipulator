import serial
import time
from comandos import Arm

'''
def pisca(tempo=3):
    conexao.write(b'a')
    time.sleep(3)
    while True:
        conexao.write(b'G28;')
        time.sleep(tempo) # Escreve 1 no arduino (LED acende)
        conexao.write(b'G1 A45;')
        time.sleep(tempo)
        conexao.write(b'G1 b90;')
        time.sleep(tempo)
        conexao.write(b'G1 c90;')
        time.sleep(tempo)

        #conexao.write(b'2') # Escreve 2 no arduino (LED apaga)
        #time.sleep(tempo) # Aguarda n segundos
        '''
if __name__ == '__main__':  # Executa a função

    braco = Arm('/dev/ttyUSB0')

    braco.begin()
    braco.send(b"a")
    time.sleep(2)
    braco.send(b'G28')
    time.sleep(2)
    braco.junta1(45)
    time.sleep(2)

    print("tudo safe")

    # pisca()