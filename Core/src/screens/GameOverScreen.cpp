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
            addLine(_("Congratulations, you have captured the thief and promoted!"));
            break;
        case GameState::Abort:
            addLine(_("You have aborted the mission but somebody else has taken the case and captured the thief."));
            break;
        case GameState::LostTimeout:
            addLine(_("You took a very long time and let the robber escape. Better luck next time."));
            break;
        case GameState::LostEscaped:
            addLine(_("You had cornered the thief but escaped on the last minute because they had no warrant. Try with another case."));
            break;
        default:
            addLine(_("Internal error. Oops."));
    }
    showLines();
    waitForInput();
}
