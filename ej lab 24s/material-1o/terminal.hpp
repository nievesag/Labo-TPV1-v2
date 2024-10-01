/*
 * Configuración y efectos especiales para la terminal.
 *
 * @author Rubén Rubio
 * @date septiembre de 2024
 */

#include <string>

// Adaptaciones específicas para Windows
#ifdef _WIN32

#ifdef __cpp_inline_variables
#include <windows.h>

class tpv1_terminal_setup_dummy {
	struct constructor {
		constructor() {
			// Activa la salida UTF-8
			SetConsoleOutputCP(CP_UTF8);
			// Activa las secuencias ANSI
			HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
			DWORD dwMode = 0;
			GetConsoleMode(hOut, &dwMode);
			dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
			SetConsoleMode(hOut, dwMode);
		}
	};
	static constructor ctor;
};

inline tpv1_terminal_setup_dummy::constructor tpv1_terminal_setup_dummy::ctor;

#else
#error "Ajusta la configuración del proyecto para utilizar C++17 o superior."
#endif

#endif

// Secuencias de escape ANSI para ajustar los atributos del terminal
namespace terminal {
	// Reinicia a los valores por defecto
	constexpr char RESET[] = "\x1b[0m";
	// Color de texto por defecto
	constexpr char RESET_FG[] = "\x1b[39m";
	// Color de fondo por defecto
	constexpr char RESET_BG[] = "\x1b[39m";
	// Negrita
	constexpr char BOLD[] = "\x1b[1m";
	// Cursiva
	constexpr char ITALIC[] = "\x1b[3m";
	// Subrayado
	constexpr char UNDERLINE[] = "\x1b[3m";

	// Texto en negro
	constexpr char BLACK[] = "\x1b[30m";
	// Texto en rojo
	constexpr char RED[] = "\x1b[31m";
	// Texto en verde
	constexpr char GREEN[] = "\x1b[32m";
	// Texto en amarillo
	constexpr char YELLOW[] = "\x1b[33m";
	// Texto en azul
	constexpr char BLUE[] = "\x1b[34m";
	// Texto en magenta
	constexpr char MAGENTA[] = "\x1b[35m";
	// Texto en cyan
	constexpr char CYAN[] = "\x1b[36m";
	// Texto en blanco
	constexpr char WHITE[] = "\x1b[37m";
	// Texto en negro brillante
	constexpr char BRIGHT_BLACK[] = "\x1b[90m";
	// Texto en rojo brillante
	constexpr char BRIGHT_RED[] = "\x1b[91m";
	// Texto en verde brillante
	constexpr char BRIGHT_GREEN[] = "\x1b[92m";
	// Texto en amarillo brillante
	constexpr char BRIGHT_YELLOW[] = "\x1b[93m";
	// Texto en azul brillante
	constexpr char BRIGHT_BLUE[] = "\x1b[94m";
	// Texto en magenta brillante
	constexpr char BRIGHT_MAGENTA[] = "\x1b[95m";
	// Texto en cyan brillante
	constexpr char BRIGHT_CYAN[] = "\x1b[96m";
	// Texto en blanco brillante
	constexpr char BRIGHT_WHITE[] = "\x1b[97m";

	// Fondo negro
	constexpr char BLACK_BG[] = "\x1b[40m";
	// Fondo rojo
	constexpr char RED_BG[] = "\x1b[41m";
	// Fondo verde
	constexpr char GREEN_BG[] = "\x1b[42m";
	// Fondo amarillo
	constexpr char YELLOW_BG[] = "\x1b[43m";
	// Fondo azul
	constexpr char BLUE_BG[] = "\x1b[44m";
	// Fondo magenta
	constexpr char MAGENTA_BG[] = "\x1b[45m";
	// Fondo cyan
	constexpr char CYAN_BG[] = "\x1b[46m";
	// Fondo blanco
	constexpr char WHITE_BG[] = "\x1b[47m";
	// Fondo negro brillante
	constexpr char BRIGHT_BLACK_BG[] = "\x1b[100m";
	// Fondo rojo brillante
	constexpr char BRIGHT_RED_BG[] = "\x1b[101m";
	// Fondo verde brillante
	constexpr char BRIGHT_GREEN_BG[] = "\x1b[102m";
	// Fondo amarillo brillante
	constexpr char BRIGHT_YELLOW_BG[] = "\x1b[103m";
	// Fondo azul brillante
	constexpr char BRIGHT_BLUE_BG[] = "\x1b[104m";
	// Fondo magenta brillante
	constexpr char BRIGHT_MAGENTA_BG[] = "\x1b[105m";
	// Fondo cyan brillante
	constexpr char BRIGHT_CYAN_BG[] = "\x1b[106m";
	// Fondo blanco brillante
	constexpr char BRIGHT_WHITE_BG[] = "\x1b[107m";

	// Color de texto RGB 24-bit
	inline std::string fg(short r, short g, short b) {
		return std::string("\x1b[38;2;") + std::to_string(r) + ";" + std::to_string(g) + ";" + std::to_string(b) + "m";
	}
	// Color de fondo RGB 24-bit
	inline std::string bg(short r, short g, short b) {
		return std::string("\x1b[48;2;") + std::to_string(r) + ";" + std::to_string(g) + ";" + std::to_string(b) + "m";
	}

	// Borra la pantalla sobre el cursor
	constexpr char CLEAR[] = "\x1b[1J";
	// Borra la pantalla entera
	constexpr char CLEAR_FULL[] = "\x1b[2J";
	// Borra la línea hasta el cursor
	constexpr char CLEAR_LINE[] = "\x1b[1K";
	// Borra la línea entera
	constexpr char CLEAR_LINE_FULL[] = "\x1b[2K";

	// Mueve el cursor a una posición arbitraria (empiezan en 1)
	inline std::string move(unsigned row, unsigned col) {
		return std::string("\x1b[") + std::to_string(row) + ";" + std::to_string(col) + "H";
	}
	// Mueve el cursor hacia arriba (n posiciones)
	inline std::string move_up(unsigned n = 1) {
		return std::string("\x1b[") + std::to_string(n) + "A";
	}
	// Mueve el cursor hacia abajo (n posiciones)
	inline std::string move_down(unsigned n = 1) {
		return std::string("\x1b[") + std::to_string(n) + "B";
	}
	// Mueve el cursor hacia la derecha (n posiciones)
	inline std::string move_right(unsigned n = 1) {
		return std::string("\x1b[") + std::to_string(n) + "C";
	}
	// Mueve el cursor hacia la izquierda (n posiciones)
	inline std::string move_left(unsigned n = 1) {
		return std::string("\x1b[") + std::to_string(n) + "D";
	}
};
