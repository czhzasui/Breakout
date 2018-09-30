/***********************************************************************************************************************
 * Created by czh on 18-9-30
 *
 * Version 1.0
 *
 **********************************************************************************************************************/
#include "game.h"
#include "command.h"

#define Refresh_Time 30

Game game(SCREEN_WIDTH, SCREEN_HEIGHT);
Command *command;

void mainLoop(Command *command) {
    while (!opengl_init(0)) {
        printf("opengl_init failed\n");
        usleep(100 * 1000);
    }
    game.init();
    while (GAME_QUIT != game.state) {
        QTime startTime = QTime::currentTime();

        game.processInput((float) Refresh_Time, command);

        game.update((float) Refresh_Time);

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        game.render();
        postDisplay();

        QTime stopTime = QTime::currentTime();
        int elapsed = startTime.msecsTo(stopTime);
        if ((Refresh_Time - elapsed) > 0) {
            std::this_thread::sleep_for(std::chrono::milliseconds(Refresh_Time - elapsed));
        } else {
            if (elapsed >= Refresh_Time)
                std::cout << "Error:refresh delay" << std::endl;
        }
    }
    game.destory();
}

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    command = new Command();
    std::thread loop(mainLoop, command);
    loop.detach();

    return a.exec();
}