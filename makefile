game: Game.cpp ResourceManager.cpp Player.cpp UIManager.cpp Enemy.cpp Enemies.cpp Beast.cpp Slime.cpp Obstacle.cpp ObstacleGenerator.cpp Arrow.cpp PowerUp.cpp SpinningBlade.cpp ExpBall.cpp ExpContainer.cpp ExpSpawner.cpp PlayerArrow.cpp PlayerArrowSpawner.cpp
	g++ Game.cpp ResourceManager.cpp Player.cpp UIManager.cpp Enemy.cpp Enemies.cpp Beast.cpp Slime.cpp Obstacle.cpp ObstacleGenerator.cpp Arrow.cpp PowerUp.cpp SpinningBlade.cpp ExpBall.cpp ExpContainer.cpp ExpSpawner.cpp PlayerArrow.cpp PlayerArrowSpawner.cpp -o game -lsfml-graphics -lsfml-window  lsfml-audio lsfml-system
	./game

make test: game
	./game