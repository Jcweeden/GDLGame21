#OBJS specifies which files to compile as part of the project
OBJS = main.cpp Game.h Game.cpp I_GameObject.h I_GameObject.cpp GameObject.h GameObject.cpp InputHandler.h InputHandler.cpp Vector2D.h TextureManager.h TextureManager.cpp Ball.h Ball.cpp BounceSurface.h BounceSurface.cpp CollisionManager.h CollisionManager.cpp SoundMixer.h SoundMixer.cpp GameStateManager.h GameStateManager.cpp GameState.h GameState.cpp PlayState.h PlayState.cpp Paddle.h Paddle.cpp MenuState.h MenuState.cpp Obstacle.h Obstacle.cpp


#CC specifies which compiler we're using
CC = g++

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
COMPILER_FLAGS = -w

#LINKER_FLAGS specifies the libraries we're linking against 
LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf

#OBJ_NAME specifies the name of our exectuable


#This is the target that compiles our executable
all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS)
