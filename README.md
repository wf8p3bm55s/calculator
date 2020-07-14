Сборка
---
Linux 
---
В текущем каталоге:

	mkdir build
	cd build
	cmake --clean-first build -DCMAKE_INSTALL_PREFIX="../install" ../
	make
	make install
	ctest

Исполняемые файлы будут находиться в каталоге ./install
Для запуска версии с графическим интерфейсом на Linux можно использовать приложение [CQtDeployer](https://github.com/QuasarApp/CQtDeployer)

	cqtdeployer.sh -bin ../install/QmlCalculator/bin/QmlCalculator -qmlDir ../qml_calculator -qmake %PATH_TO_QMAKE% -libDir ../install/Calclib/lib
