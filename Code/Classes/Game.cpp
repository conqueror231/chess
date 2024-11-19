#include "Game.h"
#include "WindowStateManager.h"
#include "ChessBoard.h"
#include "GameMode.h"
#include "GameLog.h"
#include <iostream>
const sf::Vector2f Game::TURN_LABEL_FOR_BLACK_POSITION(875, 240);
const sf::Vector2f Game::TURN_LABEL_FOR_WHITE_POSITION(875, 470);
const sf::Vector2f Game::BLACK_KING_COUNTER_POSITION(780, 10);
const sf::Vector2f Game::WHITE_KING_COUNTER_POSITION(780, 500);
const sf::Vector2f Game::GAME_LOG_OUTPUT_POSITION(780, 350);

Game::Game()
{
    loadTextures();
    InnitGUI();
     gameLog = &GameLog::getInstance();
}

Game::Game(sf::VideoMode videoMode_, sf::String windowTitle_)
    : IWindowActivity(videoMode_, windowTitle_)
{
    loadTextures();
    InnitGUI();
    ChessBoard::getInstance().resetBoard();
}

void Game::HandleInput() {
    sf::Event event;
    while (window->pollEvent(event)) {
        
        if (gameMode->getGameState() != GameState::InProgress) {
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(*window);

                sf::RectangleShape playAgainButton(sf::Vector2f(200, 60));
                playAgainButton.setFillColor(sf::Color(50, 205, 50));
                playAgainButton.setPosition(window->getSize().x / 2 - playAgainButton.getSize().x / 2, window->getSize().y / 2 + 80);

                if (mousePos.x >= playAgainButton.getPosition().x && mousePos.x <= playAgainButton.getPosition().x + playAgainButton.getSize().x &&
                    mousePos.y >= playAgainButton.getPosition().y && mousePos.y <= playAgainButton.getPosition().y + playAgainButton.getSize().y) {

                    WindowStateManager::getInstance().createMenu();
                }
            }
            continue;
        }
        static sf::Vector2i chessBoardStartPos(offsetXForChessBoard, offsetYForChessBoard);
        static sf::Vector2i chessBoardEndPos(offsetXForChessBoard + TileSize * 8, offsetYForChessBoard + TileSize * 8);
        sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
        if (isMouseInChessBoard(mousePos, chessBoardStartPos, chessBoardEndPos)) {
            calculateHoveredTilePosition(mousePos, chessBoardStartPos);
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                ChessPiece* selectedChessPiece = chessBoard->getChessPieceByPos(selectedTileIndexes.x, selectedTileIndexes.y);
                ChessPiece* clickedChessPiece = chessBoard->getChessPieceByPos(hoveredTileIndexes.x, hoveredTileIndexes.y);

                if (selectedChessPiece != nullptr && selectedChessPiece->isWhite != gameMode->isWhiteTurnNow()) {
                    GameLog::getInstance().addLog("Not your turn");
                    std::cout << "Not your turn" << std::endl;
                    selectedTileIndexes = sf::Vector2i(-1, -1);
                    continue;
                }


                if (selectedChessPiece && clickedChessPiece) {
                    PieceType typeOfClickedChessPiece = clickedChessPiece->GetType();
                    if (selectedChessPiece->Attack(*clickedChessPiece, false)) {
                        std::cout << "Piece at position (" << selectedTileIndexes.x << ", " << selectedTileIndexes.y
                            << ") attacks piece at position (" << hoveredTileIndexes.x << ", " << hoveredTileIndexes.y << ")." << std::endl;
                        gameMode->checkGameState();
                    }
                
                    selectedTileIndexes = sf::Vector2i(-1, -1);
                }

                else if (selectedChessPiece == nullptr && clickedChessPiece == nullptr) {
                    selectedTileIndexes = hoveredTileIndexes;
                }

                else if (selectedChessPiece == nullptr) {
                    selectedTileIndexes = hoveredTileIndexes;
                    std::cout << "Piece selected at tile (" << hoveredTileIndexes.x << ", " << hoveredTileIndexes.y << ")." << std::endl;
                }

                else if (clickedChessPiece == nullptr) {
                    if (selectedChessPiece->Move(hoveredTileIndexes, false)) {
                        std::cout << "Piece at position (" << selectedTileIndexes.x << ", " << selectedTileIndexes.y
                            << ") moved to tile (" << hoveredTileIndexes.x << ", " << hoveredTileIndexes.y << ")." << std::endl;

                
                        gameMode->checkGameState();

                    }
                    
               
                    selectedTileIndexes = sf::Vector2i(-1, -1);
                }
            }
        }
        else {
            hoveredTileIndexes = sf::Vector2i(-1, -1);
        }
    }

    if (event.type == sf::Event::Closed)
        window->close();
}

bool Game::isMouseInChessBoard(sf::Vector2i& mousePos, sf::Vector2i& chessBoardStartPos, sf::Vector2i& gamePromptEndPos)
{
    return mousePos.x >= chessBoardStartPos.x && mousePos.x <= gamePromptEndPos.x &&
        mousePos.y >= chessBoardStartPos.y && mousePos.y <= gamePromptEndPos.y;
}

void Game::calculateHoveredTilePosition(sf::Vector2i& mousePos, sf::Vector2i& chessBoardStartPos)
{

    for (int x = 0; x < 8; x++) {
        if (mousePos.x >= chessBoardStartPos.x + TileSize * (x + 1))
            continue;
        for (int y = 0; y < 8; y++) {
            if (mousePos.y >= chessBoardStartPos.y + TileSize * (y + 1))
                continue;

            hoveredTileIndexes.x = x;
            hoveredTileIndexes.y = y;
            // std::cout << "Row: " << y + 1 << ", Column: " << columnsLabels[x] << std::endl;
            break;
        }
        break;
    }
}

void Game::Draw()
{
    window->clear(sf::Color::Cyan);

    sf::Sprite background;
    sf::Texture backgroundTexture;
    backgroundTexture.loadFromFile(".../../Img/Background.png");
    background.setTexture(backgroundTexture);
    background.setPosition(0, 0);

    window->draw(background);

    // chess board
  
    sf::Sprite chessBoardBackground;
    sf::Texture chessBoardBackgroundTexture;

    chessBoardBackgroundTexture.loadFromFile(".../../Img/ChessBoardBackground.png");
    chessBoardBackground.setTexture(chessBoardBackgroundTexture);
    chessBoardBackground.setPosition(offsetXForChessBoard -75, 0);
    
    window->draw(chessBoardBackground);

    //Tiles
    sf::Texture lightTileTexture;
    sf::Texture darkTileTexture;

    if (!lightTileTexture.loadFromFile(".../../Img/WhiteTile.png") ||
        !darkTileTexture.loadFromFile(".../../Img/BlackTile.png")) {
        std::cout << "tiles loading error";
        return;
    }

    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {

            sf::RectangleShape tile(sf::Vector2f(TileSize, TileSize));
            tile.setPosition(col * TileSize + offsetXForChessBoard, row * TileSize + offsetYForChessBoard);

            
            if ((row + col) % 2 == 0) {
                tile.setTexture(&lightTileTexture); 
            }
            else {
                tile.setTexture(&darkTileTexture);   
            }

            window->draw(tile);  
        }
    }

    // chess pieces
    for (const auto& piece : chessBoard->getChessPieces()) {
        sf::Sprite pieceSprite;

        if (piece->isWhite)
            pieceSprite.setTexture(pieceTextures[piece->GetType()].first);
        else
            pieceSprite.setTexture(pieceTextures[piece->GetType()].second);

        pieceSprite.setPosition((piece->GetPosition().x * TileSize) + offsetXForChessBoard, (piece->GetPosition().y * TileSize + offsetYForChessBoard));

        window->draw(pieceSprite);
    }

    sf::Font font;
    if (!font.loadFromFile(".../../Fonts/beer money.ttf")) {
        std::cerr << "Failed to load font!\n";
    }
    //hovering tiles
    if (hoveredTileIndexes.x != -1 && hoveredTileIndexes.y != -1) {
        sf::RectangleShape highlightedTile(sf::Vector2f(TileSize, TileSize));
        highlightedTile.setPosition(hoveredTileIndexes.x * TileSize + offsetXForChessBoard,
            hoveredTileIndexes.y * TileSize + offsetYForChessBoard);
        highlightedTile.setFillColor(sf::Color(135, 215, 255, 128));
        window->draw(highlightedTile);
    }
    // Hovering selected Tile
    if (selectedTileIndexes.x != -1 && selectedTileIndexes.y != -1) {
        sf::RectangleShape highlightedTile(sf::Vector2f(TileSize, TileSize));
        highlightedTile.setPosition(selectedTileIndexes.x * TileSize + offsetXForChessBoard,
            selectedTileIndexes.y * TileSize + offsetYForChessBoard);
        highlightedTile.setFillColor(sf::Color(0, 0, 0, 100));
        window->draw(highlightedTile);
    }
    //Hints for moving pieces
     if (ChessPiece* piece = chessBoard->getChessPieceByPos(selectedTileIndexes.x, selectedTileIndexes.y))
    {
         sf::Sprite hintSprite;
         sf::Texture hintTextureForMoving;
         sf::Texture hintTextureForAttacking;
         hintTextureForMoving.loadFromFile(".../../Img/hintOnTile.png");
         hintTextureForAttacking.loadFromFile(".../../Img/hintOnAttack.png");
       for (sf::Vector2i pos : chessBoard->getAllPositionsWherePieceCanMove(piece)) {
         
           if(chessBoard->getChessPieceByPos(pos.x, pos.y))
               hintSprite.setTexture(hintTextureForAttacking);
           else
               hintSprite.setTexture(hintTextureForMoving);
           hintSprite.setPosition(pos.x * TileSize + offsetXForChessBoard, pos.y * TileSize + offsetYForChessBoard);
            window->draw(hintSprite);
        }
    }
    
    
    // Which turn is it 
    sf::Text turnLabel;
    turnLabel.setFont(font);
    turnLabel.setCharacterSize(30);
    turnLabel.setFillColor(gameMode->isWhiteTurnNow() ? sf::Color::White : sf::Color::Black);
    turnLabel.setString(gameMode->isWhiteTurnNow() ? "White Turn" : "Black Turn");
    sf::Vector2f pos = gameMode->isWhiteTurnNow() ? TURN_LABEL_FOR_WHITE_POSITION : TURN_LABEL_FOR_BLACK_POSITION;
    turnLabel.setPosition(pos);
    window->draw(turnLabel);


    //Count of captured pieces
    sf::Sprite kingSprite;
    sf::Texture kingTexture;
    kingTexture.loadFromFile(".../../Img/BlackKingForCounter.png");
    kingSprite.setTexture(kingTexture);
    kingSprite.setPosition(BLACK_KING_COUNTER_POSITION);
    window->draw(kingSprite);
    kingTexture.loadFromFile(".../../Img/WhiteKingForCounter.png");
    kingSprite.setPosition(WHITE_KING_COUNTER_POSITION);
    window->draw(kingSprite);

    sf::Vector2f OffsetForBlackPawns = { WHITE_KING_COUNTER_POSITION.x - 35,WHITE_KING_COUNTER_POSITION.y + 200 };
    sf::Vector2f OffsetForWhitePawns = { BLACK_KING_COUNTER_POSITION.x - 35,BLACK_KING_COUNTER_POSITION.y + 200 };
    sf::Vector2f OffsetForBlackNotPawns = { WHITE_KING_COUNTER_POSITION.x + 10,WHITE_KING_COUNTER_POSITION.y + 200 };
    sf::Vector2f OffsetForWhiteNotPawns = { BLACK_KING_COUNTER_POSITION.x + 10,BLACK_KING_COUNTER_POSITION.y + 200 };
    for (const std::pair<PieceType, bool>& capturedPiece : ChessBoard::getInstance().GetCapturedPiecesTypes()) {
     
        static float stepXForPawns = 7;  
        static float stepXForNotPawns = 16;
        sf::Sprite capturedPieceSprite;
        capturedPieceSprite.scale(0.5, 0.5);
        sf::Texture texture = capturedPiece.second ? pieceTextures[capturedPiece.first].first : pieceTextures[capturedPiece.first].second;
        capturedPieceSprite.setTexture(texture);
       
       if (capturedPiece.second) {

           if (capturedPiece.first == PieceType::Pawn) {
               capturedPieceSprite.setPosition(OffsetForWhitePawns);
               OffsetForWhitePawns.x += stepXForPawns;
           }
           else {
               capturedPieceSprite.setPosition(OffsetForWhiteNotPawns);
               OffsetForWhiteNotPawns.x += stepXForNotPawns;
           }

       }
      else {
           if (capturedPiece.first == PieceType::Pawn) {
               capturedPieceSprite.setPosition(OffsetForBlackPawns);
               OffsetForBlackPawns.x += stepXForPawns;
           }
           else {
               capturedPieceSprite.setPosition(OffsetForBlackNotPawns);
               OffsetForBlackNotPawns.x += stepXForNotPawns;
           }
      }
       window->draw(capturedPieceSprite);
    }

    //right output
    sf::Text gameOutputLog;
    gameOutputLog.setFont(font);
    gameOutputLog.setCharacterSize(20);
    gameOutputLog.setFillColor(sf::Color::Black);
    
    sf::String ouputLog = GameLog::getInstance().getLog();
    gameOutputLog.setString(ouputLog);

    gameOutputLog.setPosition(GAME_LOG_OUTPUT_POSITION);
    window->draw(gameOutputLog);
    //End of game  
    if (gameMode->getGameState() == Checkmate || gameMode->getGameState() == Stalemate) {
        sf::Text winMessage;
        winMessage.setFont(font);
        winMessage.setCharacterSize(60);
        winMessage.setFillColor(sf::Color::Yellow);

        std::string text;

        if (gameMode->getGameState() == Checkmate)
            text = gameMode->isWhiteTurnNow() ? "White wins by checkmate" : "Black wins by checkmate";
        if (gameMode->getGameState() == Stalemate)
            text = "Stalemate";

        winMessage.setString(text);

        winMessage.setPosition(window->getSize().x / 2 - winMessage.getGlobalBounds().width / 2,
            window->getSize().y / 2 - winMessage.getGlobalBounds().height / 2);

        sf::RectangleShape overlay(sf::Vector2f(window->getSize().x, window->getSize().y));
        overlay.setFillColor(sf::Color(0, 0, 0, 150));
        window->draw(overlay);

        
        window->draw(winMessage);

        if (gameMode->getGameState() == Checkmate || gameMode->getGameState() == Stalemate) {
            sf::Text winMessage;
            winMessage.setFont(font);
            winMessage.setCharacterSize(60);
            winMessage.setFillColor(sf::Color::Yellow);

            std::string text;

            if (gameMode->getGameState() == Checkmate)
                text = gameMode->isWhiteTurnNow() ? "White wins by checkmate" : "Black wins by checkmate";
            if (gameMode->getGameState() == Stalemate)
                text = "Stalemate";

            winMessage.setString(text);

            winMessage.setPosition(window->getSize().x / 2 - winMessage.getGlobalBounds().width / 2,
                window->getSize().y / 2 - winMessage.getGlobalBounds().height / 2);


            sf::RectangleShape overlay(sf::Vector2f(window->getSize().x, window->getSize().y));
            overlay.setFillColor(sf::Color(0, 0, 0, 150));
            window->draw(overlay);

          
            window->draw(winMessage);

            // Play Again button
            sf::RectangleShape playAgainButton(sf::Vector2f(250, 70));
            playAgainButton.setFillColor(sf::Color(240, 230, 140)); 
            playAgainButton.setOutlineColor(sf::Color(200, 190, 120)); 
            playAgainButton.setOutlineThickness(4);
            playAgainButton.setPosition(window->getSize().x / 2 - playAgainButton.getSize().x / 2,
                window->getSize().y / 2 + 100);

    
            sf::RectangleShape buttonShadow(playAgainButton.getSize());
            buttonShadow.setFillColor(sf::Color(0, 0, 0, 80)); 
            buttonShadow.setPosition(playAgainButton.getPosition().x + 5, playAgainButton.getPosition().y + 5);
            window->draw(buttonShadow);

          
            window->draw(playAgainButton);

         
            sf::Text playAgainText;
            playAgainText.setFont(font);
            playAgainText.setString("Back to menu");
            playAgainText.setCharacterSize(30);
            playAgainText.setFillColor(sf::Color::Black);
            playAgainText.setPosition(
                playAgainButton.getPosition().x + playAgainButton.getSize().x / 2 - playAgainText.getGlobalBounds().width / 2,
                playAgainButton.getPosition().y + playAgainButton.getSize().y / 2 - playAgainText.getGlobalBounds().height / 2);

     
            window->draw(playAgainText);
        }

    }

     
    window->display();
}

void Game::Run()
{
    IWindowActivity::Run();
}

void Game::InnitGUI()
{
    chessBoard = &ChessBoard::getInstance();
    gameMode = new GameMode();
}

void Game::loadTextures()
{
    pieceTextures[PieceType::Pawn].first.loadFromFile(".../../Img/Pawn_W.png");
    pieceTextures[PieceType::Pawn].second.loadFromFile(".../../Img/Pawn_B.png");
    pieceTextures[PieceType::Rook].first.loadFromFile(".../../Img/Rook_W.png");
    pieceTextures[PieceType::Rook].second.loadFromFile(".../../Img/Rook_B.png");
    pieceTextures[PieceType::Knight].first.loadFromFile(".../../Img/Knight_W.png");
    pieceTextures[PieceType::Knight].second.loadFromFile(".../../Img/Knight_B.png");
    pieceTextures[PieceType::Bishop].first.loadFromFile(".../../Img/Bishop_W.png");
    pieceTextures[PieceType::Bishop].second.loadFromFile(".../../Img/Bishop_B.png");
    pieceTextures[PieceType::Queen].first.loadFromFile(".../../Img/Queen_W.png");
    pieceTextures[PieceType::Queen].second.loadFromFile(".../../Img/Queen_B.png");
    pieceTextures[PieceType::King].first.loadFromFile(".../../Img/King_W.png");
    pieceTextures[PieceType::King].second.loadFromFile(".../../Img/King_B.png");
}