#include "menu.h"

//		   _____							//
//		  /     \   ____   ____  __ __		//
//		 /  \ /  \_/ __ \ /    \|  |  \		//
//		/    Y    \  ___/|   |  \  |  /		//
//		\____|__  /\___  >___|  /____/		//
//		        \/     \/     \/			//

void Menu::MenuFrame(IDirect3DDevice9* pDirectDevice)
{
	// Creates menu window
	ImGui::Begin("Menu", &bOpen);
	{
		// Render a textbox
		ImGui::Text("Example text");

		// Render a checkbox
		static bool bChecked = true;
		ImGui::Checkbox("Example checkbox", &bChecked);

		ImGui::End(); // End of window
	}
}