### 步骤1：安装jupyter 

下载地址及安装方法：https://www.continuum.io/downloads

###  步骤2：安装spark

下载spark http://spark.apache.org/ 
解压：tar zxvf   spark-2.1.0-bin-hadoop2.7.tgz

### 步骤3：配置jupyter登录

产生密码：终端输入ipython
In [1]: from IPython.lib import passwd
In [2]: passwd()
Enter password: 
Verify password: 
Out[2]: 'sha1:6402ac25a515:2755b924b8bb5bef2475f7918776197e2f972858'

配置参数：
进入/root/.jupyter/jupyter_notebook_config.py
c.NotebookApp.ip = '*'   #启动服务的地址，设置成 ‘*’ 可以从同一网段的其他机器访问到；
c.NotebookApp.open_browser = False     #启动 ipython notebook 的时候不会自动打开浏览器；
c.NotebookApp.password = 'sha1:6402ac25a515:2755b924b8bb5bef2475f7918776197e2f972858'  # ipython notebook的登陆密码
c.NotebookApp.port = 6666 #设置访问端口 每次启动ipthon notebook端口会加1 

### 步骤4：设置环境变量

进入 vim ~/.bashrc 或 vi ~/.bashrc 在最后添加
export JAVA_HOME=/root/jdk1.8   #jdk路径
export SPARK_HOME=/root/spark2.1 #spark的路径
export PYSPARK_PYTHON=python3   
export PYTHONPATH=$SPARK_HOME/python/lib/py4j-0.10.4-src.zip // 替换对应版本的py4j
export PATH="$PATH:$JAVA_HOME/bin:$SPARK_HOME/bin:$PATH"

### 步骤5：后台启动

nohup jupyter notebook &

### 步骤6：访问 ip:6666

### 步骤7  配置环境变量

PYSPARK_PYTHON=python3 PYSPARK_DRIVER_PYTHON=ipython PYSPARK_DRIVER_PYTHON_OPTS="notebook"./bin/pyspark
或
spark2.0以下：IPYTHON=1 IPYTHON_OPTS=notebook ./spark/bin/pyspark
或
PYSPARK_DRIVER_PYTHON=ipython3 PYSPARK_DRIVER_PYTHON_OPTS="notebook" ./bin/pyspark