#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>

int main(int argc, char *argv[]) {
    
    if (argc != 5) {
        std::cout << "Parametri: " << argv[0] << " <num_copie> <peso (1 = 1Kb)> <nome_file> <path_directory>" << std::endl;
        return 1;
    }

    int peso = 1;
    int num_file = std::stoi(argv[1]); // Utilizza std::stoi per la conversione
    std::string nome_file = argv[3];
    std::string path_dir = argv[4];
    peso *= std::stoi(argv[2]);     // moltiplica il peso di ogni file

    // Crea la cartella se non esiste
    std::filesystem::create_directories(path_dir);

    for (int j = 0; j < num_file; ++j) {
        std::string path_del_file = path_dir + "/" + nome_file + std::to_string(j); // Usa std::to_string per convertire j in stringa

        std::ofstream outfile(path_del_file);

        if (outfile.is_open()) {

            for (int i = 0; i <= peso; ++i) {
                outfile << "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000" << std::endl;
                outfile << "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000" << std::endl;
                outfile << "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000" << std::endl;
                outfile << "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000" << std::endl;
                outfile << "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000" << std::endl;
                outfile << "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000" << std::endl;
                outfile << "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000" << std::endl;
                outfile << "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000" << std::endl;
                outfile << "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000" << std::endl;
				outfile << "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000" << std::endl;
            }

            outfile.close(); // Chiudi il file dopo la scrittura
        } 
		else {
            std::cerr << "Errore nell'aprire il file: " << path_del_file << std::endl;
        }
    }

    return 0; // Termina con successo
}
