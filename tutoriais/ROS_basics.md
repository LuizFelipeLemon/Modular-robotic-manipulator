Packages(Pacotes): ROS utiliza pacotes para organizar seus programas. Vocês pode pensar
de um pacote como todos os arquivos que um programa ROS específico contém.(.cpp,.py,arquivos
de configuração, arquivos de compilação, etc). Sendo estes arquivos organizados em pacotes
com a seguinte estrutura:

diretório launcher: contém arquivos launch
diretório src: contém arquivos source(cpp, python)
CMakeLists.txt: lista de regras cmake para compilação
package.xml: informação de pacotes e dependências

catkin workspace: local para criar pacotes ROS
	roscd (você será jogado para o diretório catkin_ws/devel)
	cd .. (utilizando este comando, você irá voltar um diretório, indo para catkin_wk)
	cd src (criar todos os pacotes dentro desta pasta)
	catkin_create_pkg <package_name> <package_dependecies> (criar novo pacote)
	EX: catkin_create_pkg my_package rospy

Para ir para o diretório de qualquer pacote ROS:
	roscd <package_name>

Para checar os pacotes criados:
	rospack list: mostra uma lista de todos os pacotes no sistema ROS
	rospack list | grep my_packages: filtra de todos os pacotes o pacote chamado "my_packages"
	roscd my_packages: leva para a localização do diretório do pacote "my_packages"

Criar um launch diretório dentro do pacote:  ROS utiliza arquivos launch para executar programas
	roscd <package_name>
	mkdir launch
	touch launch/<package_name>_launch_file.launch
	Dentro do launch, modificar o launch de acordo com o que você quiser
	EX: <launch>
  		<!-- turtlebot_teleop_key already has its own built in velocity smoother -->
  		<node pkg="turtlebot_teleop" type="turtlebot_teleop_key.py" name="turtlebot_teleop_keyboard"  output="screen">
    			<param name="scale_linear" value="0.5" type="double"/>
    			<param name="scale_angular" value="1.5" type="double"/>
    			<remap from="turtlebot_teleop_keyboard/cmd_vel" to="/cmd_vel"/>   <!-- cmd_vel_mux/input/teleop"/-->
 		 </node>
		</launch>
	EX2: <launch>
    		<!-- My Package launch file -->
    		<node pkg="my_package" type="simple.py" name="ObiWan"  output="screen">
    		</node>
	      </launch>
	
	Todos os arquivos launch contém tags, onde é especificado os seguintes parâmetros:
		1.pkg = 'package_name': nome do pacote que contém o código do programa ROS
			a ser executado.
		2.type = 'python_file_name.py': nome do arquivo de programa que quer ser executado
		3.name = 'node_name': Nome do ROS node(nó ou módulo) que irá lançar(launch)
			o arquivo python
		4.output = 'type_of_output': através de qual canal será mostrado a saída do 
			arquivo python.

Lançar um pacote(launch):
	roslaunch <package_name> <launch_name>.launch
	EX: roslaunch my_package my_package_launch_file.launch
	As vezes é necessario refresh o ROS para reconhecer o novo pacote:
	rospack profile

Caso dê erro de permissão no arquivo .py: é comum ocorrer problemas quando trabalhando com python
scripts, normalmente isso ocorre quando os arquivos python não tem permissão de execução e
para resolver este problema, basta fazer o seguinte:
	Na pasta do código:
	ls -la (checa as permissões de um arquivo dentro do diretório)
	chmod +x name_of_file.py
	ls -la (se ficar com o nome verde, ok)

ROS nodes: nodes(nó ou módulos) são basicamente programas feito em ROS
	rosnode list: lista todos os nodes rodando no computador
	rosnode info /<node_name>: informação sobre o node específico

Compilação de pacote:
	No diretório do catkin_work:
	catkin_make (compila todos os pacotes)
	catkin_make --only-pkg-with-deps <package_name> (compila o pacote específico)

Parametro server: é um dicionário que o ROS utiliza para guardar parâmetros
	rosparam list: gera uma lista com todos os parametros
	rosparam get <parameter_name>: pega um parametro especifico
	rosparam set <parameter_name> <value>:modifica o valor de um parametro

Roscore: é o processo principal que gerencia todo o sistema ROS, é sempre necessário ter 
um roscore rodando para trabalhar com ROS:
	roscore: comando que lança o roscore 
