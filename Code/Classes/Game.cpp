#include "Game.h"
#include "WindowStateManager.h"
#include "ChessBoard.h"
#include <iostream>

Game::Game()
{
    loadTextures();
    InnitGUI();
}

Game::Game(sf::VideoMode videoMode_, sf::String windowTitle_)
    : IWindowActivity(videoMode_, windowTitle_)
{
    loadTextures();
    InnitGUI();

}

void Game::HandleInput()
{
    sf::Event event;
    while (window->pollEvent(event))
    {
        static sf::Vector2i chessBoardStartPos(offsetXForChessBoard, offsetYForChessBoard);
        static sf::Vector2i chessBoardEndPos(offsetXForChessBoard + TileSize * 8,
                                                        offsetYForChessBoard + TileSize * 8);
        sf::Vector2i mousePos = sf::Mouse::getPosition(*window);

        if (isMouseInChessBoard(mousePos, chessBoardStartPos, chessBoardEndPos)) {

            calculateHoveredTilePosition(mousePos, chessBoardStartPos);

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            ChessPiece* selectedChessPiece = chessBoard->getChessPieceByPos(selectedTileIndexes.x, selectedTileIndexes.y);
            ChessPiece* clickedChessPiece = chessBoard->getChessPieceByPos(hoveredTileIndexes.x, hoveredTileIndexes.y);
            
            if (selectedChessPiece && clickedChessPiece) {
                if (selectedChessPiece->Attack(*clickedChessPiece))
                {
                    std::cout << "Piece at position (" << selectedTileIndexes.x << ", " << selectedTileIndexes.y
                        << ") attacks piece at position (" << hoveredTileIndexes.x << ", " << hoveredTileIndexes.y << ")." << std::endl;
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
                if (selectedChessPiece->Move(hoveredTileIndexes)) {
                    std::cout << "Piece at position (" << selectedTileIndexes.x << ", " << selectedTileIndexes.y
                        << ") moved to tile (" << hoveredTileIndexes.x << ", " << hoveredTileIndexes.y << ")." << std::endl;
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

void Game::Update()
{

}

void Game::Draw()
{
    window->clear(sf::Color::Cyan);
    
   // chess board
    sf::Color lightColor = sf::Color::White;
    sf::Color darkColor(73, 84, 202);
   
    
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
           
            sf::RectangleShape tile(sf::Vector2f(TileSize, TileSize));
            tile.setPosition(col * TileSize + offsetXForChessBoard, row * TileSize + offsetYForChessBoard);

            if ((row + col) % 2 == 0) {
                tile.setFillColor(lightColor); 
            }
            else {
                tile.setFillColor(darkColor);  
            }

            window->draw(tile);
        }
    }
    
    // chess pieces
    for (const auto& piece : chessBoard->getChessPieces()) {
        sf::Sprite pieceSprite;

        if(piece->isWhite)
            pieceSprite.setTexture(pieceTextures[piece->GetType()].first);
        else
            pieceSprite.setTexture(pieceTextures[piece->GetType()].second);
        
        pieceSprite.setPosition((piece->GetPosition().x * TileSize) + 260, (piece->GetPosition().y * TileSize + 25) );
   
        window->draw(pieceSprite);
    }
    //left side menu 
    
    sf::RectangleShape rectangle;
    rectangle.setSize(sf::Vector2f(203, 768));
    rectangle.setFillColor(sf::Color(17, 140, 202));  
    window->draw(rectangle);
    

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
    for (int i = 0; i < 8; ++i) {
        sf::Text rowLabel;
        rowLabel.setFont(font);
        rowLabel.setString(std::to_string(8 - i)); 
        rowLabel.setCharacterSize(24);
        rowLabel.setFillColor(sf::Color::Black);
        rowLabel.setPosition(offsetXForChessBoard - 30, i * TileSize + offsetYForChessBoard + TileSize / 4);
        window->draw(rowLabel);

        sf::Text colLabel;
        colLabel.setFont(font);
        colLabel.setString(std::string(1, 'A' + i)); 
        colLabel.setCharacterSize(24);
        colLabel.setFillColor(sf::Color::Black);
        colLabel.setPosition(i * TileSize + offsetXForChessBoard + TileSize / 3, offsetYForChessBoard + 8 * TileSize);
        window->draw(colLabel);
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
