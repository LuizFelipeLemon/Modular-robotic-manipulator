Actions(ações) são como chamadas assíncronas para serviços, sendo bem similiar. Quando é
chamado uma ação, você está chamando uma funcionalidade que outro node está provendo, o mesmo
que com os serviços. A diferença é que quando seu node chama um serviço, deve esperar até o
serviço terminar, porém quando seu node chama uma ação, não necessariamente tem-se que esperar
até a ação terminar.

Portanto, é dito que uma ação é uma chamada assíncrona para outra funcionalidade de node.
O node que provê a funcionalidade deve conter um 'action server', que permite que outros nodes
chame aquela funcionalidade do node. E o node que chama a funcionalidade tem que conter um
'action cliente', que permite um node conectar ao 'action server' de outro node.

Chamar um 'action server' significa mandar uma mensagem pra ele. Do mesmo jeito com os
topics e services, que funciona por passagem de mensagens.
- A mensagem de um topic é composto de uma só parte: a informação que o tópico provê;
- A mensagem de um service tem duas partes: o pedido e a resposta; 
- A mensagem de um action server é dividido em 3 partes: o objetivo, o resultado e o feedback.

Devido ao fato de chamar um action server não interrompe sua thread. action servers provê uma
mensagem chamada 'feedback'. O feedback é uma mensagem que o action server gera a cada momento
para indicar como a ação está indo, informando o status da ação pedida, e é gerada enquanto
a ação está em progesso.

ROS Actions: http://wiki.ros.org/actionlib

How actions work: http://wiki.ros.org/actionlib/DetailedDescription

http://docs.ros.org/en/jade/api/actionlib/html/classactionlib_1_1simple__action__client_1_1SimpleActionClient.html