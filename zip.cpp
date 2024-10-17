#include <zip.h>
#include <iostream>
#include <filesystem>  // C++17 per la gestione dei filesystem
#include <string>

// Funzione per comprimere tutti i file in una cartella
bool zip_folder(const std::string& folder_path, const std::string& zip_filename) {
    int errorp;
    zip_t* zf = zip_open(zip_filename.c_str(), ZIP_CREATE | ZIP_TRUNCATE, &errorp);
    if (!zf) {
        std::cerr << "Errore nella creazione del file ZIP: " << zip_filename << std::endl;
        return false;
    }

    // Iterazione attraverso tutti i file della cartella usando filesystem senza namespace
    for (const auto& entry : std::filesystem::recursive_directory_iterator(folder_path)) {
        if (entry.is_regular_file()) {
            std::string file_path = entry.path().string();
            std::string relative_path = std::filesystem::relative(entry.path(), folder_path).string();

            zip_source_t* source = zip_source_file(zf, file_path.c_str(), 0, 0);
            if (!source || zip_file_add(zf, relative_path.c_str(), source, ZIP_FL_OVERWRITE) < 0) {
                zip_source_free(source);
                std::cerr << "Errore durante l'aggiunta del file all'archivio ZIP: " << relative_path << std::endl;
                zip_close(zf);
                return false;
            }

            std::cout << "Aggiunto file: " << relative_path << " al file ZIP." << std::endl;
        }
    }

    zip_close(zf);
    std::cout << "Cartella compressa con successo in: " << zip_filename << std::endl;
    return true;
}

int main(int argc, char* argv[]) {
    // Verifica se ci sono abbastanza argomenti
    if (argc != 3) {
        std::cerr << "Utilizzo: " << argv[0] << " <cartella_da_comprimere> <nome_output_zip>" << std::endl;
        return 1;
    }

    // Prendere i parametri da argv
    std::string folder_path = argv[1]; // Percorso della cartella da comprimere
    std::string zip_filename = argv[2]; // Nome del file ZIP di output

    // Verifica se il percorso specificato è una directory
    if (!std::filesystem::is_directory(folder_path)) {
        std::cerr << "Errore: " << folder_path << " non è una directory valida." << std::endl;
        return 1;
    }

    // Chiamare la funzione zip_folder con i parametri dati
    if (!zip_folder(folder_path, zip_filename)) {
        std::cerr << "Errore durante la compressione della cartella." << std::endl;
        return 1;
    }

    return 0;
}
