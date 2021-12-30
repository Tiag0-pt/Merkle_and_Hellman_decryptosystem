import sys
import os
import numpy as np
import matplotlib.pyplot as plt


###################################################################################################
# python3 hs.txt bf.txt ... function.txt                                                          #
# output -> grafico.png                                                                           #
###################################################################################################

# Tirem os prints iniciais

graph_names = []
for i in range(1,len(sys.argv)):
    dados = sys.argv[i]
    graph_name = dados.split('/')[-1].split('.')[0]
    os.system("cat {0} | grep Linha -v > {1}".format(dados,'grafico.png'))
    dados_file = open('grafico.png','r')
    dados = []
    n = 10
    x_axis = [10]


    while True:
        
        sum_ = 0
        line = dados_file.readline().strip().split(' ')   
        for i in line:
            try:
                sum_ += float(i)
            except:
                continue
        if sum_==0:
            break
        dados.append(sum_/20)
        n += 1
        x_axis.append(n)
    x_axis.pop()
    dados = np.log(np.array(dados))
    r = np.polyfit(x_axis,dados,1)
    print("{0} -> m={1} b = {2}".format(graph_name,r[0],r[1]))
    plt.plot(x_axis, dados)
    graph_names.append(graph_name)
#plt.show()
plt.grid(True)
plt.legend(graph_names)
plt.xlabel('n')
plt.ylabel('log(t(s))')
plt.savefig('grafico.png')
   
    






