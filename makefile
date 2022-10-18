game:Game.cpp ResourceManager.cpp Player.cpp UIManager.cpp Enemy.cpp Enemies.cpp Beast.cpp Slime.cpp Obstacle.cpp ObstacleGenerator.cpp Arrow.cpp SpinningBlade.cpp SpinningBladeSpawner.cpp ExpBall.cpp ExpContainer.cpp ExpSpawner.cpp PlayerArrow.cpp PlayerArrowSpawner.cpp GameLoader.cpp -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
	g++ Game.cpp ResourceManager.cpp Player.cpp UIManager.cpp Enemy.cpp Enemies.cpp Beast.cpp Slime.cpp Obstacle.cpp ObstacleGenerator.cpp Arrow.cpp SpinningBlade.cpp SpinningBladeSpawner.cpp ExpBall.cpp ExpContainer.cpp ExpSpawner.cpp PlayerArrow.cpp PlayerArrowSpawner.cpp GameLoader.cpp -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -o game

make test: game
	./game