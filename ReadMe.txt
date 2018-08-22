1. 开发平台：VS2008 SP1

2. 系统：windows7

3. 工程配置：
			 项目->项目属性->配置属性->常规->字符集：设为多字节字符集
			 项目->项目属性->配置属性->C/C++->常规->附加包含目录：xxx/mysql-5.6.36-win32/include
			 项目->项目属性->配置属性->连接器->常规->附加库目录：xxx/mysql-5.6.36-win32/lib
			 项目->项目属性->配置属性->连接器->输入->附加依赖项：libmysql.lib
			 把xxx/mysql-5.6.36-win32/lib/libmysql.dll放到工程目录下
			 注意：mysql是32位的，且必须开启服务 net start mysql

4. 数据库版本：mysql-5.6.36-win32

5. 版本控制：Git