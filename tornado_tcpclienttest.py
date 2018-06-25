#tcp_client.py
from tornado import ioloop,gen,iostream
from tornado.tcpclient import TCPClient
@gen.coroutine
def Trans():
    stream=yield TCPClient().connect('localhost',8760)
    try:
        for msg in('zzxxc','abcde','i feel lucky','over'):
            yield stream.write(bytes(msg,'utf-8'))
            back=yield stream.read_bytes(20,partial=True)
            print(back)
    except iostream.StreamClosedError:
        pass

if __name__=='__main__':
    ioloop.IOLoop.current().run_sync(Trans)