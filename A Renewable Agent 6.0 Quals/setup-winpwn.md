1. `winget install Microsoft.WinDbg`
2. `pip install winpwn`
3. `pip install pykd`
4. `https://github.com/Byzero512/peda-windows/tree/master/windbg/bywin`
5. `https://github.com/0vercl0k/windbg-scripts/tree/master/telescope`
6. `https://github.com/Wenzel/checksec.py/releases/tag/v0.7.4`

refs  
- https://github.com/leesh3288/WinPwn
- https://zeyadazima.com/notes/osednotes/#windbg-automation-with-python
- https://ctftime.org/writeup/16974
- https://zaratec.io/awesome-windows-ctf/

deploys  
- https://blog.thalium.re/posts/sstic_infra_windows/

note:
- there's no windbgx.debug() so the process actually already being ran before attached so some breakpoints are not hit.