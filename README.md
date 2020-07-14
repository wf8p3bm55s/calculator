Сборка
---
Linux 
---
В текущем каталоге:
В проекте используется Qt 5.15.0.

	mkdir build
	cd build
	cmake --clean-first build -DCMAKE_PREFIX_PATH=%PATH_TO_QT%/5.15.0/gcc_64 -DCMAKE_INSTALL_PREFIX="../install" ../
	make
	make install
	ctest

Исполняемые файлы будут находиться в каталоге ./install
Для запуска версии с графическим интерфейсом на Linux можно использовать приложение [CQtDeployer](https://github.com/QuasarApp/CQtDeployer)

	cqtdeployer.sh -bin ../install/QmlCalculator/bin/QmlCalculator -qmlDir ../qml_calculator -qmake %PATH_TO_QMAKE% -libDir ../install/Calclib/lib

В тестовой сборке использовался CQtDeployer v1.4.5.
Для запуска приложения с графическим интерфейсом может потребоваться установка libxcb-xinerama0.
    
    sudo apt-get install libxcb-xinerama0