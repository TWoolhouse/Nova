import sys
from pathlib import Path
from typing import TextIO

done = set()

mainfile = Path(sys.argv[1]).absolute().resolve()
root = mainfile.parent

INCLUDE = "#include"
def expand(out: TextIO, filename: Path):
	REL_NAME = filename.as_posix()[len(root.as_posix())+1:]
	out.write(f"// File: {REL_NAME}\n\n")
	print("Import>", filename)
	with filename.open() as file:
		for line in file:
			lline = line.lstrip()
			if lline.startswith(INCLUDE):
				if ((ang_s := line.find("\"")) != -1 and (ang_e := line.find("\"", ang_s+1)) != -1)\
				or ((ang_s := line.find("\'")) != -1 and (ang_e := line.find("\'", ang_s+1)) != -1):
					include_name = line[ang_s+1:ang_e]
					# print(f"Evaluate: {include_name} @ {filename}")
					flag = True
					for sdir in (filename.parent, root):
						include = (sdir / include_name).resolve()
						if include.is_file() and not include.match((root / "vendor/**/*.h").as_posix()):
							if include.as_posix() not in done:
								# print(f"Import: {include}")
								expand(out, include)
							break
					else:
						flag = False
					if flag:
						continue
			elif lline.startswith("#pragma") and (pragma_line := line.strip().split(maxsplit=1)) and len(pragma_line) == 2 and pragma_line[1] == "once":
				done.add(filename.as_posix())
				continue
			out.write(line)
	out.write(f"// File: !{REL_NAME}\n")

with (root / (sys.argv[2] if len(sys.argv) > 1 else "out.h")).open("w") as file:
	file.write("#pragma once\n")
	expand(file, mainfile)
