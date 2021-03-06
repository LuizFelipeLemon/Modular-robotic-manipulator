# Instalação do Ecossistema para utilização do ROS em windows subsystem for linux (WSL) :mechanical_arm:
No momento, só é possível utilizar ROS em ambiente linux, porém, para os usuários de windows
que possuem a versão Windows 10 instalado em seu PC é possivel instalar um terminal Ubuntu
com o Windows Subsystem for Linux (WSL), permitindo desenvolver aplicações em ambiente linux
no sistema operacional windows. Neste tutorial iremos abordar todo o procedimeto necessário para utilização do ROS em windows subsystem for linux, 
contendo as referências necessárias para rodar e resolver possíveis erros.

## Instalação do WSL2
Nossa primeira referência é o tutorial da microsoft para instalação do WSL2. Siga as instruções desse [Tutorial](https://docs.microsoft.com/en-us/windows/wsl/install-win10) e retorne aqui. Sigam os **Manual Installation Steps**, escolham **WSL 2 as your default version** e instalem **Ubuntu 20.04 LTS** na Microsoft Store. Também recomendo a instalação do **Windows Terminal**. Você também pode acompanhar em vídeo essa mesma instalação [aqui](https://youtu.be/WWPQAvHG35M). 

## Instalação do ROS

Nesso momento você realizará os próximos passos no linux instalad, portanto abra o Windows terminal e crie uma aba do Ubuntu clicando no icone :arrow_down_small: e selecionando Ubuntu 20.04.
Caso não tenha instalado o Windows terminal basta pesquisar Ubuntu na barra de pesquisa do menu iniciar e será mostrada a tela do terminal do Ubuntu 20.04.

Este tutorial será para a instalação da distribuição do ROS Noetic, você também pode acompanhar o tutorial oficial [aqui.](http://wiki.ros.org/noetic/Installation/Ubuntu). Primeiramente, será necessário 
configurar seu computador em ordem de fazer o download do pacote do site packages.ros.org.
Para isso, copie e cole o seguinte comando no terminal ubuntu:

```bash
sudo sh -c 'echo "deb http://packages.ros.org/ros/ubuntu $(lsb_release -sc) main" > /etc/apt/sources.list.d/ros-latest.list'
```
Em seguida, fará o download da chave do servidor utilizando o seguinte comando:

```bash
sudo apt-key adv --keyserver hkp://ha.pool.sks-keyservers.net:80 --recv-key 421C365BD9FF1F717815A3895523BAEEB01FA116
```
Agora sua máquina está pronta para instalar o ROS, mas antes, será necessário atualizar-lá
para deixar todas as configurações nas versões mais recentes:

```bash
sudo apt-get update
sudo apt dist-upgrade
```

Agora, para instalar todos os pacotes básicos do ROS para começar a trabalhar, é recomendado
instalar a versão Desktop FUll:

```bash
sudo apt-get install ros-noetic-desktop-full
```
O processo de instalação pode demorar alguns minutos.

Até este ponto, foi instalado, se tudo ocorreu corretamente, algumas ferramentas básicas que
o ROS provê. Mas caso você tenha a necessidade de instalar um pacote específico do ROS, basta
utilizar o seguinte comando:

```bash
sudo apt-get install ros-noetic-<PACKAGE_NAME>
```
Você deverá rodar esse script para cada terminal que abrir:
```bash
source /opt/ros/noetic/setup.bash
```

Mas você pode automaticamete adicionar o ambiente de variáveis ROS para
sua sessão bash cada vez que um novo terminal for lançado. Para isso, em vez de 
utilizar o comando `source /opt/ros/noetic/setup.bash` toda vez que abrir um novo terminal,
é mais prático adicionar ao seu .bashrc para que já execute esse comando automáticamente:
```bash
echo "source /opt/ros/noetic/setup.bash" >> ~/.bashrc
```

>Também, este processo permite que você instale várias distribuições ROS no mesmo computador
e troque entre elas. Por exemplo, se você também tinha o ROS indigo instalado em seu computador
você pode trocar entre ambas as distribuições utilizando os seguintes comandos: 

>source /opt/ros/indigo/setup.bash (Para utilizar Indigo)

>source /opt/ros/noetic/setup.bash (Para utilizar noetic)



Por fim instalamos todas as dependências necessárias para utilizarmos Pacotes ROS:

```bash
sudo apt install python3-rosdep python3-rosinstall python3-rosinstall-generator python3-wstool build-essential ros-noetic-ros-control ros-noetic-ros-controllers ros-noetic-catkin python3-catkin-tools ros-noetic-gazebo-ros-pkgs ros-noetic-gazebo-ros-control python3-osrf-pycommon ros-noetic-moveit-ros-visualization ros-noetic-moveit-planners-ompl

```

Antes de começar a utilizar o ROS, será necessário inicializar o rosdep, que facilitará a
instalação das dependências do sistema e também é requerido para funcionar alguns componentes
chaves do ROS.

```bash
sudo rosdep init
rosdep update
```

## Criar um espaço de trabalho Catkin e clonar algum projeto de robótica ao diretório

Pronto, até este ponto, já foi instalado e configurado tudo que é necessário para utilizar
os pacotes ROS. Porém, ainda falta gerenciar seu local de trabalho ROS, para isso, será 
utilizado o diretório `catkin_ws`, este diretório é chamado de catkin workspace ou ROS
workspace e é basicamente o local onde você colocará todos os novos pacotes ROS que você
criar. Para criar esse diretório, utilize o seguinte comando:

```bash
mkdir -p ~/mynew_ws/src #pode substituir o mynew_ws por qualquer nome de sua preferência
cd ~/mynew_ws/src
git clone https://github.com/erdalpekel/panda_simulation.git #Este projeto é de um braço robótico Panda da empresa Franka Emika
git clone https://github.com/erdalpekel/panda_moveit_config.git
git clone --branch simulation https://github.com/erdalpekel/franka_ros.git
cd ..
sudo apt-get install libboost-filesystem-dev
rosdep install --from-paths src --ignore-src -y --skip-keys libfranka
cd ..
```

É também importante que você "build" a biblioteca libfranka da fonte e passe seu diretório para
o 'catkin build' quando compilando este pacote ROS como descrito [nesse tutorial](https://frankaemika.github.io/docs/installation_linux.html).

A seguir irá instalar qualquer pacote ROS que ainda não esteja instalado em seu espaço de espaço.

```bash
cd ~/mynew_ws/src
rosdep install -y --from-paths . --ignore-src --rosdistro noetic
cd ..
catkin config --extend /opt/ros/${ROS_DISTRO} --cmake-args -DCMAKE_BUILD_TYPE=Release
catkin build #Sempre necessário realizar essa etapa caso acrescente algum pacote, nodes e afins dentro da pasta de trabalho catkin
```

Importante mencionar, que se encontrar algum problema durante o processo de compilação do
'catkin build', é bem normal e dependendo do erro é possível encontrar soluções pesquisando no google.
Não postarei aqui, pois podem ser diversos problemas dependendo do computador do usuário.

Se der tudo certo ao compilar o diretório de trabalho caktin, é sempre necessário após o processo
de compilação adicionar à sessão bashrc.

```bash
source ~/mynew_ws/devel/setup.bash #sempre mude o nome da pasta para o que você esteja utilizando
echo 'source ~/mynew_ws/devel/setup.bash' >> ~/.bashrc
```

Agora para ter certeza que seu local de trabalho está conectado ao ambiente ROS, rode o seguinte
comando:
```bash
source devel/setup.bash
echo $ROS_PACKAGE_PATH
```

A documentação oficial para o processo de instalação pode ser encontrado neste [site.](http://wiki.ros.org/noetic/Installation)


## Instalação do Gazebo

Para proceder a instalação do Gazebo basta seguir a [documentação oficial](http://gazebosim.org/tutorials?tut=ros_installing&cat=connect_ros) e instalar com apenas a seguinte linha:
```bash
curl -sSL http://get.gazebosim.org | sh
```

Antes de testar se a instalação funcionou, siga os passos contido nesse [vídeo](https://youtu.be/DW7l9LHdK5c) para instalação e configuração do **VcXsrv Windows X Server**. Ao finalizar os passos você será capaz de testar tanto o gazebo quanto o rviz: 

```bash
gazebo
```
ou 

```bash
rviz
```

Esta etapa constuma falhar bastante então caso as interfaces não esteja aparecendo repita completamente o tutorial do [vídeo](https://youtu.be/DW7l9LHdK5c). Além disso, adicionar os seguintes comandos ao ~/.bashrc também evita a ocorrência de erros:

```bash
echo "export GAZEBO_IP=127.0.0.1" >> ~/.bashrc
echo "export DISPLAY=$(cat /etc/resolv.conf | grep nameserver | awk '{print $2}'):0" >> ~/.bashrc
echo "export LIBGL_ALWAYS_INDIRECT=0" >> ~/.bashrc
```

## MoveIt

A partir daqui você deverá seguir os [Tutoriais oficiais do MoveIt](https://ros-planning.github.io/moveit_tutorials/).





