from socket import *
from os.path import exists

HOST = 'ec2-13-125-33-40.ap-northeast-2.compute.amazonaws.com'
PORT = 1825

server_socket = socket(AF_INET, SOCK_STREAM)
server_socket.bind((HOST, PORT))
server_socket.listen(1)

while True:
    try:
        connection_socket, addr = server_socket.accept()
        print(str(addr), '에서 접속했습니다.')

        filename = connection_socket.recv(1024)
        print('파일 다운로드 요청: ', filename.decode('utf-8'))
        data_transferred = 0

        if not exists(filename):
            print(str(filename, 'utf-8'), '이(가) 존재하지 않습니다.')
        else:
            print('파일 %s 전송 시작' % filename)
            with open(filename, 'rb') as f:
                data = f.read(1024)
                while data:
                    data_transferred += connection_socket.send(data)
                    data = f.read(1024)
            print('전송완료 %s, 전송량 %d' % (filename, data_transferred))
        connection_socket.close()
    except Exception as ex:
        print(ex)
        connection_socket.close()
