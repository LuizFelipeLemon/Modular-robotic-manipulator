Nodes utilizam tópicos para publicar informação para outros nodes para que possam se comunicar

Para encontrar tópicos no sistema:
	rostopic list: lista de todos os tópicos presentes no sistema
	rostopic list | grep '<name_of_topic>': filtra a lista de tópicos
	rostopic info <name_of_topic>: informação sobre um tópico

Publisher é um node que continua publicando uma mensagem em um tópico. Um tópico é um canal
que age como um cano, onde os outros ROS nodes podem publicar ou ler informação

Comando relacionados a tópicos:
	rostopic echo <topic_name>: ler a informação que está sendo publicado em um tópico
	rostopic echo <topic_name> -n1: ler somente a última mensagem publicada em um tópico
	rostopic -h: pode checar diferentes opções que o comando rostopic fornece

Para executar um código:
	rosrun <package_name> <code_name>.py


Tópicos lidam com informações através de mensagens, há diferentes tipos de mensagens, porém 
é aconselhável utilizar as mensagens padrões do ROS quando possível. Mensagens sçai definidos 
nos arquivos .msg, na quais são localizados dentro um msg diretório de um pacote.

Para conseguir informação sobre um mensagem:
	rosmsg show <message>
	EX: rosmsg show std_msgs/Int32

Publicar um tópico:
	rostopic pub <topic_name> <message_type> <value>: irá publicar a mensagem que você
		especificar com o valor que você especificar no tópico que você especificar

Subscriber é um node que ler informação de um tópico.

ROS Topics: http://wiki.ros.org/Topics

ROS Messages: http://wiki.ros.org/Messages

msg Files: http://wiki.ros.org/msg

Publisher and Subscriber 1: http://wiki.ros.org/ROS/Tutorials/WritingPublisherSubscriber%28python%29

Publisher and Subscriber 2: http://wiki.ros.org/ROS/Tutorials/ExaminingPublisherSubscriber
