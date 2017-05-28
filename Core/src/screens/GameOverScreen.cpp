#include "GameOverScreen.h"

#include "entities/PlayersManager.h"

GameOverScreen::GameOverScreen(Renderer* renderer, Game* game, PlayerCase* playerCase) :
ComputerScreen(renderer),
game(game),
playerCase(playerCase) {

}

void GameOverScreen::show() {
    switch (game->getGameState()) {
        case GameState::Won:
            PlayersManager::updatePlayer(playerCase->getPlayer());
            addLine(_("Congratulations, you have won the case and promoted!"));
            break;
        case GameState::Abort:
            addLine(_("The mission has been aborted, fortunately was all a hoax."));
            break;
        case GameState::LostTimeout:
            addLine(_("You took a long time and the robber has escaped. Try again with another case."));
            break;
        case GameState::LostEscaped:
            addLine(_("What a shame! You had cornered the thief but escaped because they had no warrant. Try with another case."));
            break;
        default:
            addLine(_("Internal error. Oops."));
    }
    showLines();
    waitForInput();
}
