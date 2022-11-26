import os
import matplotlib.pyplot as plt

def main():
    #logファイルから生値を取得
    nama_data = read_log_file()

    #lpfをかけた値を取得
    lpf_data = lpf(nama_data)

    # グラフの表示
    plt.plot(range(len(nama_data)), nama_data, color="blue")
    plt.plot(range(len(lpf_data)), lpf_data, color="red")
    plt.xlim(0,1500)
    plt.ylim(0,1024)
    plt.xticks(range(0, len(nama_data)+500, 500))
    plt.yticks(range(0, 1100, 100))
    plt.show()
    
# log読んで生値を取得
def read_log_file():
    os.chdir('C:/Users/yuto/Documents/Program/octdeer/saltydog/log')
    log_file = open('log.log')
    log_data = log_file.readlines()
    log_file.close()
    for i in range(len(log_data)):
        log_data[i] = log_data[i].strip()
        log_data[i] = int(log_data[i])
    
    return log_data

# LPF
def lpf(nama_data):
    lpf1 = LPF(0.6)
    lpf2 = LPF(0.6)

    lpf_data = []
    for i in nama_data:
        lpf_data.append(lpf2.lpf(lpf1.lpf(i)))

    return lpf_data
    
# LPF class
class LPF:
    a = 0
    y = 0
    
    def __init__(self, val):
        self.a = val
        
    def lpf(self, x):
        self.y = self.a * self.y + (1 - self.a) * x
        return self.y

if __name__ == '__main__':
    main()
