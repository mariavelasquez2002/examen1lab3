#include "examenreproductor.h"
#include <QtWidgets/QApplication>
#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>
#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>

// Enumeración para los géneros de música
enum class Genero {
    POP,
    ROCK,
    RAP,
    DANCE,
    REGGAE,
    ELECTRONICA,
    RANCHERA
};

// Clase para manejar los archivos
class CTunes {
private:
    std::fstream codigosFile;
    std::fstream songsFile;
    std::fstream downloadsFile;

public:
    CTunes() {
        codigosFile.open("codigos.itn", std::ios::in | std::ios::out | std::ios::binary);
        songsFile.open("songs.itn", std::ios::in | std::ios::out | std::ios::binary);
        downloadsFile.open("downloads.itn", std::ios::in | std::ios::out | std::ios::binary);

        if (!codigosFile.is_open() || !songsFile.is_open() || !downloadsFile.is_open()) {
           
            codigosFile.close();
            songsFile.close();
            downloadsFile.close();

            std::ofstream createCodigos("codigos.itn", std::ios::binary);
            std::ofstream createSongs("songs.itn", std::ios::binary);
            std::ofstream createDownloads("downloads.itn", std::ios::binary);

            if (!createCodigos.is_open() || !createSongs.is_open() || !createDownloads.is_open()) {

                // Si aún así no se pudieron crear los archivos, lanzar una excepción
                throw std::runtime_error("Error al crear archivos.");
            }

            // Inicializar con 1 y 1 si los archivos se crearon
            int firstSongCode = 1;
            int firstDownloadCode = 1;
            createCodigos.write(reinterpret_cast<char*>(&firstSongCode), sizeof(int));
            createCodigos.write(reinterpret_cast<char*>(&firstDownloadCode), sizeof(int));
        }
    }

    ~CTunes() {
        codigosFile.close();
        songsFile.close();
        downloadsFile.close();
    }

    int getCodigo(long offset) {
        int codigo;
        codigosFile.seekg(offset);
        codigosFile.read(reinterpret_cast<char*>(&codigo), sizeof(int));
        int nuevoCodigo = codigo + 1;
        codigosFile.seekp(offset);
        codigosFile.write(reinterpret_cast<char*>(&nuevoCodigo), sizeof(int));
        return codigo;
    }

    void addSong(std::string nombre, std::string cantante, Genero genero, double precio) {
        int codigo = getCodigo(0);
        songsFile.seekp(0, std::ios::end);
        songsFile.write(reinterpret_cast<char*>(&codigo), sizeof(int));
        songsFile.write(nombre.c_str(), nombre.size() + 1);
        songsFile.write(cantante.c_str(), cantante.size() + 1);
        songsFile.write(reinterpret_cast<char*>(&genero), sizeof(Genero));
        songsFile.write(reinterpret_cast<char*>(&precio), sizeof(double));
        int estrellas = 0;
        int reviews = 0;
        songsFile.write(reinterpret_cast<char*>(&estrellas), sizeof(int));
        songsFile.write(reinterpret_cast<char*>(&reviews), sizeof(int));
    }
};

class AddSongWindow : public QWidget {
    Q_OBJECT

public:
    AddSongWindow(CTunes* ctunes) : ctunes(ctunes) {
        QVBoxLayout* layout = new QVBoxLayout();
        setLayout(layout);

        QFormLayout* formLayout = new QFormLayout();
        layout->addLayout(formLayout);

        titleLabel = new QLabel("Title:");
        titleLineEdit = new QLineEdit();
        formLayout->addRow(titleLabel, titleLineEdit);

        artistLabel = new QLabel("Artist:");
        artistLineEdit = new QLineEdit();
        formLayout->addRow(artistLabel, artistLineEdit);

        genreLabel = new QLabel("Genre:");
        genreLineEdit = new QLineEdit();
        formLayout->addRow(genreLabel, genreLineEdit);

        priceLabel = new QLabel("Price:");
        priceLineEdit = new QLineEdit();
        formLayout->addRow(priceLabel, priceLineEdit);

        addButton = new QPushButton("Add");
        connect(addButton, SIGNAL(clicked()), this, SLOT(addSong()));
        layout->addWidget(addButton);
    }

private slots:
    void addSong() {
        std::string title = titleLineEdit->text().toStdString();
        std::string artist = artistLineEdit->text().toStdString();
        std::string genreStr = genreLineEdit->text().toStdString();
        double price = priceLineEdit->text().toDouble();

        // Convertir el string del género a enum
        Genero genre;
        if (genreStr == "POP") {
            genre = Genero::POP;
        }
        else if (genreStr == "ROCK") {
            genre = Genero::ROCK;
        }
        else if (genreStr == "RAP") {
            genre = Genero::RAP;
        }
        else if (genreStr == "DANCE") {
            genre = Genero::DANCE;
        }
        else if (genreStr == "REGGAE") {
            genre = Genero::REGGAE;
        }
        else if (genreStr == "ELECTRONICA") {
            genre = Genero::ELECTRONICA;
        }
        else if (genreStr == "RANCHERA") {
            genre = Genero::RANCHERA;
        }
        else {
            QMessageBox::warning(this, "Error", "Invalid genre.");
            return;
        }

        try {
            ctunes->addSong(title, artist, genre, price);
            QMessageBox::information(this, "Success", "Song added successfully.");
            clearFields();
        }
        catch (const std::exception& e) {
            QMessageBox::critical(this, "Error", e.what());
        }
    }

private:
    void clearFields() {
        titleLineEdit->clear();
        artistLineEdit->clear();
        genreLineEdit->clear();
        priceLineEdit->clear();
    }

    CTunes* ctunes;
    QLabel* titleLabel;
    QLabel* artistLabel;
    QLabel* genreLabel;
    QLabel* priceLabel;
    QLineEdit* titleLineEdit;
    QLineEdit* artistLineEdit;
    QLineEdit* genreLineEdit;
    QLineEdit* priceLineEdit;
    QPushButton* addButton;
};

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    CTunes ctunes;
    AddSongWindow window(&ctunes);
    window.setWindowTitle("Add Song");
    window.show();

    return app.exec();
}

#include "main.moc"