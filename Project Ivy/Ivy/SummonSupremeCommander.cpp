#include "SummonSupremeCommander.h"

void SummonSupremeCommander::Execute(std::vector<boost::any> arglist)
{
	std::cout
		<< ":::::::::::::::::::::::::::::::::::::::~~=~::::::::::::::::::::::::::::::::::~~~"
		<< "::::::::::::::::::::::::::::::::::7DNDNNNNNNNNN8=:::::::::::::::::::::::::~~:~~~"
		<< ":::::::::::::::::::::::::::::~+$8OD888OO8888D888DNO:::::::::::::::::::::::::~~~~"
		<< "::::::::::::::::::::::::::::~ZZ7III$$7III77$$ZOO8DDD7~::::::::::::::::::::::~~~~"
		<< "::::::::::::::::::::::::::::8III?+==+=========+=+??788~::::::::::::::::::::~~:~~"
		<< "::::::::::::::::::::::::::=Z77?+===~=~~~~~~~=====+??I$8$::::::::::::::::::::~~~~"
		<< ":::::::::::::::::::::::::+$$7I+===~~::::::~~:~~===+?I7$O7:::::::::::::::::::~~~~"
		<< "::::::::::::::::::::::::=ZZ$I?==~:~~:::::::::::~~==?I77I8I~:::::::::::::::::::~~"
		<< "::::::::::::::::::::::::8$Z7?+==~~~~~::::::::~::~~=+I7IIIO:::::::::::::::::::~~~"
		<< "::::::::::::::::::::::~ZZ$$I?+===~~:::~:::~:~~~~~~=+IIIIIZI::::::::::::::::::~::"
		<< "::::::::::::::::::::::78Z$$I++==~~:::~::::::::::~~=+???II8D~:::::::::::::::::~~~"
		<< "::::::::::::::::::::::O88$$?+=~~~::,,,,,,,,:::::~~=+?+?I7ONI:::::::::::::::~::~~"
		<< ":::::::::::::::::::::~DDOZII++~~~::::::,::::::~~===++?II7ZD$::::::::::::::::::~~"
		<< ":::::::::::::::::::::Z8NOO88OOZZ$$7+~~~~=?77I???+?I??I7I8OD8=~::::::::::::::::~~"
		<< "::::::::::::::::::::+ZMMDNZZI7$ZZZ$$OI+?II7OOZ77I+7OI8MMMMNM$~::::::::::::~~~~~~"
		<< "::::::::::::::::::::+ONDOO$ZO77?=I?7?:~=8I?7~7ZZ$OZ$MNO77ONMZ+:::::::::::::::~~~"
		<< "::::::::::::::::::::=78O8$$$7+~=+?+Z=:==$=?I=:~=+$Z$Z7??7OMN$=::::::::::::::::~~"
		<< ":::::::::::::::::::::78O$ZZ??+++==II=:===~~===+?+++7+???IZND$:::::::::::::::~~~~"
		<< ":::::::::::::::::::::~=I$I?+====~~=I~:===:~=+=+?I??==+II7O$$+::::::::::::::::~~~"
		<< "::::::::::::::::::::::=?$I=~:::::+??:,~=++~:,,::::~==?I?IZZI:::::::::::::::::~~~"
		<< "::::::::::::::::::::::~?$?=~:,:~~++I=:++:~I~=:,,:::==+??I$7I:::::::::::::::::~~~"
		<< "::::::::::::::::::::::~I$?~~::==~+$$$77I$Z+~~+~:::~=++??77?=:::::::::::::::::~~~"
		<< "::::::::::::::::::::::~7$?=~~+++IZZ$7$7?7ZI+==?=~~=+==?I$II:::::::::::::::::::::"
		<< ":::::::::::::::::::::::I7++~+7?+++?++==~++?++?I++~~==+?$$:::::::::::::::::::::::"
		<< ":::::::::::::::::::::::+7?=:??I8N7~,,:,,,~I$O7I$=::==+I$I::::::::::::::::::::~~~"
		<< "::::::::::::::::::::::::$I+:~+~~?$~,....,~IZ7~??=~~++?ZO?::::::::::::::::::::~:~"
		<< "::::::::::::::::::::::::$I?~:I=~~++=~~=+=~+~~=$$~~=?+7OZ~:::::::::::::::::::::~~"
		<< "::::::::::::::::::::::::~87+~7?+~~~:::::::~~=?$Z+=?7ZOZ?~::::::::::::::::::::~~~"
		<< ":::::::::::::::::::::::::I8$$$I$I+~~=~==~::=III$77IZOO~:::::::::::::::::::::::::"
		<< "::::::::::::::::::::::::::=8O7777??++++++=+IIIII$7Z8ZZMO::::::::::::::::::::::~~"
		<< "::::::::::::::::::::::::::8N8Z?I+?+=~~~~~=??=II7$ODOZZMM+::::::::::::::::::::~~~"
		<< ":::::::::::::::::::::::::NMMOO$7+++=======+?I$OZ8DO$7ZMMMI:::::::~~::::::::~~~~~"
		<< "::::::::::::::::::::::::MMMNOZ88ZI7?I???I?+7O8DDO77?IOMMMM8+:~~+~:~:::~~~~~~~~~~"
		<< "::::::::::::::::::~:::INMMMMZ7OOD8O77OZ$OZ$O88OZ$II?7ZMMMMMMM7:7+~~~~~~~~~~~~~~~"
		<< ":::::::::::::::::~8MMMMMMMMM7III$Z8NNDD888OZ$III?++??NMMMMMMMMMMMNO=:~~~~~~~~~~~"
		<< ":::::::::::::=7DMMMMMMMMMMMM7?+++?7$777$III?I?~=~==+?MMMDNMMMMMMMMMNNN7=:~~~~~~~"
		<< ":::::=ODN87MMMMMMMMMMMMMDNMMO??+~==++?++===~~~~~:~=?OMNNMMNMMMMMMMMMMMNNNN$~~~~~"
		<< "::+OD+ZDMMMMMMMMMMMMMMNNMNMMM+===~:~~==~~~~~~::::=+INMMMMMMNMMMMMMMMMMMMMMMNNZ~~"
		<< "MMMMMMMMMMMMMM8DNNNNNMMMMMNMMO==~:,,:::~~~:::,,:~=DMMMMMMMMMMDMMMMMMMMMMMMMMMMMM"
		<< "MMMMMMMMMMMMMMMMMMMMMMMMMMMMNNZ+~~:,,,,,:,:,,,::=?DMMMMMMMMMMMMMNNMMMMMMMMMMMMMM"
		<< "MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMN$:::,,,,,,,,,,::=NMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM"
		<< "MMNNMMMMMMMMMMMMMMMMMMMMMMMMMMMMNMM$~,,,,,,,,:=INMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM"
		<< "MMMNMMMMMMMMMMMMMMMMMMMMMMMMMMMNMMNMMMMMMMMMMMMNMMMNMMNNMMMMMMMMMMMMMMMMMMMMMMMM"
		<< "MMMNMMMMMMMMMMMMMMMMMMMMMMNNMMMNMMMNMMMMMMMMMMNMMMMNMMNNMMMMMMMMMMMMMMMMMMMMMMMM"
		<< "MMMMMMMMMMMMMMMMMMMMMNMMMNNNMNNMNMMMNMMMMMMMMMMMMMNNMMNNMMMMMMMMMMMMMMMMMMMMMMMM"
		<< "NMMNMMMMMMMMMMMMMMMMMNMMMNMNNNMMMNMMMNMMMMMMMMMMMNNNMMNNMMMMMMMMMMMMMMMMMMMMMMMM"
		<< "NMMNMMMMMMMMMMMMMMMMMMMMMNNNNNMMNNNMMMMMMMMNMMMMMNNNMMNNNMMMMMMMMMMMMMMMMMMMMMMM"
		<< "MMMMMMMMMMMMMMMMMMMMMMMMNMMNNNMMNMNNMMMMMMNMMMMMNNNNNMNNNMMNMMMMMMMMMMMMMMMMMMMM"
		<< "MMMMMMMMMMMMMMMMMMMMMNMMNNNNNNMMMNNNNMMMMMMMMMMNNNNNNMNNNMMMMMMMMMMMMMMMMMMMMMMM"
		<< "MNMMNMMMMMMMMMMMMMMMMNMMNNNNNNMMNNNNNMNMMMMNMMNNNNNNNMNNMNNMMMMMMMMMMMMMMMMMMMMM"
		<< "MNMNNMNNMNMMMNMMMMMMMNMMNNNNNNMMNNNNNMMMNMMNNNNNNNNNNMNNMNNNMMMMMMMMMMMMMMMMMMMM";
}

boost::any SummonSupremeCommander::GetResult()
{
	return Result;
}

SummonSupremeCommander::~SummonSupremeCommander()
{
}


