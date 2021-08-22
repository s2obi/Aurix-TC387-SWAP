from socket import *
import os
import sys
import can
import time

# Socket Configuration
HOST = 'ec2-13-125-33-40.ap-northeast-2.compute.amazonaws.com'
PORT = 1825

# CAN Configuration
bustype = 'socketcan_native'
channel = 'can0'

# 업데이트 서버에서 Hex 파일 다운로드
def hexDownload():
    try:
        client_socket = socket(AF_INET, SOCK_STREAM)
        print('--------------------------------------------------')
        print('Start download get to hex file from OTA server')
        print('[Hex-Download]Trying to connect server...')
        client_socket.connect((HOST, PORT))
        print('[Hex-Download]Socket Connection Success!')

        filename = 'LineTracer_Base.hex'
        client_socket.sendall(filename.encode('utf-8'))

        print('[Hex-Download]Request Download...')
        data = client_socket.recv(1024)
        data_transferred = 0
        if not data:
            print('[Hex-Download]There is no file such as filename: %s' %filename)
            return False
        
        print('[Hex-Download]Start Download into %s' %os.getcwd()+'/'+filename)
        currentDir = os.getcwd()
        with open(currentDir+'/'+filename, 'wb') as f: # 현재 경로에 filename으로 파일을 받는다.
            while data: # data가 있을 때까지
                f.write(data) # 1024 바이트 쓴다.
                data_transferred += len(data)
                data = client_socket.recv(1024) # 1024 바이트를 받아온다.
        print('[Hex-Download]File %s download completed! transferred %d bytes' %(filename, data_transferred))
        print('[Hex-Download]Socket close')
        client_socket.close()
        return True
    except Exception as ex:
        print('[Hex-Download]Exception - %s' %ex)
        return False

# Hex 파일 전송
def transmit_hex():
    print('--------------------------------------------------')
    print('Transfer hex file to MCU')
    path = os.getcwd() + '/LineTracer_Base.hex'
    print('[Hex-Transfer]Open file: %s' %path)
    f_hex = open(path, 'r')
    print('[Hex-Transfer]Transfer starting...')
    time.sleep(5)
    try:
        while True:
            line = f_hex.readline()
            line = line.strip() # 줄 바꿈 문자 제거
            if not line: break
            can_send(id=0x10, msg=line)
            can_send(id=0x09, msg='rec_OK') # 한 레코드 전송 완료
        f_hex.close()
        print('[Hex-Transfer]Transfer completed! send message \'txHex_OK\'')
        can_send(0x11, 'txHex_OK')
    except Exception as ex:
        print('[Hex-Transfer]Error - %s' %ex)
        print('[Hex-Transfer]Transfer aborted!')
        can_send(0x12, 'txHexERR')
        print(ex)

# CAN 메시지 전송 처리
def can_send(id, msg):
    split_length = 8
    split_msg = [msg[i:i+split_length] for i in range(0, len(msg), split_length)] # 데이터 전송을 위해 8바이트 단위로 자른다.

    for i in split_msg:
        print('[CAN tx] ID: ', hex(id), '| DLC: ', len(i), '| Data: ', bytearray(i.encode()).hex(),  i, '|')
        txMsg = can.Message(arbitration_id=id, data=bytearray(i.encode()), extended_id=False)
        bus.send(txMsg)
        time.sleep(0.001) # 1ms마다 메시지 전송

# CAN Initialization
bus = can.interface.Bus(channel=channel, bustype=bustype)
print('Channel:', bus.channel_info)
print('CAN Bus State: ', bus.state)

# Gateway Services
while True:
    rxMsg = bus.recv(1.0)
    if rxMsg is not None:
        print('[CAN Rx] ID: ', hex(rxMsg.arbitration_id), '| DLC: ', rxMsg.dlc, '| Data: ', rxMsg.data.hex(), rxMsg.data.decode(), '|')

        # Request OTA Update
        if rxMsg.arbitration_id is 0x100:
            if hexDownload() is True: # Hex 다운로드가 완료되면 MCU로 Hex 전송
                transmit_hex()
            else:
                print('Hex Download Failed. reprogramming aborted.')
                can_send(0x04, 'DWH_Fail')
