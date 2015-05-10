# FileCopyEx - version history #

## Version 2.0.0 beta (in testing) ##
  * Moving to Far 2 API.
  * Full Unicode support (removed many OEM/ANSI re-encodings).
  * x86 и x64 versions.
  * Memory management refactored - strings and containers replaced to C++ stl - fixed error "Framework index size limit exceeded".
  * Small bug fixes (dialogs shadows and so on).
  * Custom queue panel removed.
  * Memory leaks removed.
  * Copy progress added to application task bar icon under windows 7.

## Version 1.9.0 beta (bugfixes by Axxie & slst) ##
  * Implemented checking of Esc press during directories scanning. Now Esc cancels operation.
  * Progress indication has been added to the directories scanning dialog. The dialog show number and total size of scanned files.
  * Free space on the destination drive is checked before copying.
  * Hot keys in copy and overwrite dialogs are now similar to the standard hot keys.
  * Directories scanning is now faster than before.
  * After rename cursor is moved to the new file name.
  * Quotes are completely ignored in destination path.
  * Bug with help is fixed. Only Russian help is available.
  * Bug with network target paths is fixed again. Previous fix didn't work for network share top-level directories.
  * Bug with streams copying in NT4 is fixed.
  * Bug with silent copy dialog closing if source and destination paths were the same is fixed. Now error message appears in this case.
  * Plugin was not able to start from directory with non-ANSI name. Fixed.
  * Now plugin correctly works with files, which are opened by another process. If a file is open for writing by another process, plugin shows error message. The new option that allows reading files opened for writing from other processes has been added.
  * Bug with incorrect time estimation in copying in parallel mode is fixed.
  * File names were displayed incorrectly during copying. Fixed.
  * Waiting for the user reply was added to the elapsed time, but not to the total time. Fixed.
  * Plugin was not able to copy directory to the nul in 9x. Fixed.
  * Now plugin does not break hard links.
  * Volume Mount Points were not handled correctly. Fixed.
  * Plugin was not able to copy file if access to one of the parent directories was not granted. Fixed.
  * Plugin was not able to copy symbolic link from different machine on the network. Fixed.
  * Bug with encoding in 9x is fixed. Plugin sometimes was not able to copy files in 9x because of this bug.
  * Bug with attributes cleaning if file is renamed with case changing only is fixed.
  * Bug with description entry deletion if file is renamed with case changing only is fixed.
  * Bug with description entry doubling if file with description was overwritten is fixed.
  * If while copying files, some of them were skipped, it could lead plugin to skip other files, which needed to be copied. Fixed.

## Version 1.8.2 beta (bugfixes by Axxie [axxie-no-spam@filecopyex.org.ua ](.md)) ##
  * Initial state auto-detection of the &quot;Allow parallel copy&quot; checkbox now works in NT4.
  * &quot;Allow parallel copy&quot; was allowed by default when user pressed Shift-F5/Shift-F6. Fixed.
  * Denis Porfiryev has kindly allowed to include his FileCopyEx AutoAW plugin in the package.
  * Visual Studio 6 project has been added.
  * Fixed bug with network target paths.
  * Fixed bug with setting &quot;Encrypted&quot; attribute.
  * Changed hotkeys for &quot;Rename&quot; action (thanks to CDK).
  * Fixed bug with error message during moving file with streams from one partition to another (thanks to CDK).
  * [experimental](experimental.md) Thousands delimiter is now space (previously comma was used).

## Version 1.8.1 alpha (bugfixes by CDK) ##
  * Improved compatibility with FAR plugin panels containing real file names (TempPanel, Branch).
  * [experimental](experimental.md) Fixed low speed issue when copying to Flash media.
  * [experimental](experimental.md) Color of the progress dialog labels is changed to dark-blue.

## Version 1.8 beta (bugfixes by slst [slst-remove-me@mail333.com ](.md)) ##
  * Plugin hanged during copying of symbolic links. Fixed.
  * Sometimes copying of recursive symbolic links resulted in stack overflow. Fixed.
  * Quotes in destination name/path resulted in &quot;error creating output file&quot;. Fixed.
  * &quot;Allow parallel copy&quot; checkbox initial state auto-detection didn't work in Windows 2000. Fixed.
  * FDLG\_WARNING style added for &quot;ask for overwrite&quot; dialog (red background color).
  * FileCopyExW.dll (Unicode version) was tested on Windows 2000 SP4 / Far v1.70 alpha 6 build 2039.
  * FileCopyExA.dll (ANSI version) was not tested.

## Version 1.7 beta (author of versions prior to 1.8 - craZZy [crazzy-remove-me@magnusoft.com ](.md)) ##
  * Description files with spaces and russian characters in file names correctly processed.
  * Fixed bugs with copying files from queue in Far 1.70b5.
  * ESC correctly handled during confirmation of copying termination.

## Version 1.6 beta ##
  * Disk space preallocation for large files (threshold is adjustable).
  * Added "Confirm termination by ESC" setting.
  * "GetSectorSize failed" fixed.
  * Fixed parallel copy crash bug.
  * More accurate time calculation.
  * A little bit improvement of small files copying.
  * Added "Append" feature (always works in buffered mode).
  * Small fixes.
  * Included plugin source code.

## Version 1.5 beta ##
  * UNICODE support.
  * Fixed bug with calling Extended Copy from plugin panels (e.g., archive).
  * Copy queue, which is a more convinient&nbsp;implementation of temporary panel.
  * Unbuffered read and write, which should speed up copy operation even more.
  * Option to limit reading/writing speed.
  * Resuming after copying was cancelled by user or interrupted due to an error.
  * Extended error handling: "Skip All" button, an option to reopen the file before retrying (for recovering after network failures).
  * Precise detection of different physical devices on Windows XP.
  * Bugs with descriptions are hopefully fixed :)
  * Option to use CONNECT-like progressbars.
  * Many other features...

> This version was totally rewritten, many old bugs were fixed, but new ones might have been introduced. Bugs found in this beta: (please note bugs marked with <b>(?)</b>. These bugs were hopefully fixed and should not appear. If one of them do appear, please let me know about it. Don't forget to give a detailed description of the situation that caused the bug. Also, let me know if you find a bug which is not in this list)
    * Some descriptions may not be copied if copying was aborted by the user.
    * Append mode not implemented.
    * Putting skipped files to temporary panel not implemented.
    * Renaming files in Win9x may be too slow.
    * Auto-rename mode is not always working.
    * (?) Copying to NUL on Win9x may not work.
    * (?) Sometimes (rarely) plugin crashes when "Parallel Copy" is on.
    * (?) "Invalid buffer" error may appear when using "Resume" mode.
    * (?) File contents may become broken after "Reopen and Retry".
    * After moving, some empty directories may remain.
    * The Help system is not yet updated.

## Version 1.34 ##
  * Renaming directories didn't work when some file inside them were opened (plugin copied and deleted then instead of just renaming).
  * Multiline description support.
  * Buffer size can now be specified both in percent of RAM size or in kilobytes.
  * Options to confirm interruption by ESC and to beep after long operations.
  * Copy progress window uses FAR colors in FAR 1.70 or higher.
  * Copying of NTFS streams now works.
  * Read-only volume warning doesn't appear anymore when copying to CD-RW.
  * Plugin now correctly works with files larger than 2GB.
  * Correct write errors handling (file is not being read after write error).
  * Some more options for description handling.
  * Descriptions were lost after renaming without moving to another directory.

> Bugs found in this version (will be fixed in next release):
    * Description handling doesn't always work properly and sometimes causes the descriptions to be lost. So, it is better to turn this option off.
    * Plugin crashes when summary size of copied files is zero.
    * When activating plugin from archive or other plugin panel, standard copy dialog must be shown, but it doesn't.

## Version 1.33 ##
  * Doesn't show "Memory allocation error" on machines with more than 128 MB of RAM.
  * Removes directories with read-only attribute.
  * Correctly saves "Clear read-only from CDs" option.

## Version 1.3 ##
  * New copy options - "Skip if destination is same or newer" and "Place skipped files to temporary panel". These options are located in Copy and Overwrite dialogs.
  * Buffer size is now specified in percent of total memory size.
  * New configuration options - "Parallel copy by default", "Clear Read-only attribute from CD", "Show advanced NTFS options".
  * NTFS-specific options are shown only in Windows NT/2000, and only if corresponding checkbox is turned on in configuration dialog.
  * There is no more need to register plugin with FileCopyEx.reg - hotkeys are set up in configuration dialog.
  * Full-featured description management, including updating descriptions in subdirectories (see help).
  * Showing total size of files currently copying.
  * Showing copy progress in console title.
  * Understanding environment variables in Copy dialog.
  * Warning when it's not possible to copy streams, rights, or to set compression and encryption attributes on destination volume, or if destination path is invalid.
  * Quick move within one device (via renaming) now works in Windows 95/98.
  * Russian and English interface.
  * Small bugs fixed.

## Version 1.02 ##
  * Access Denied now doesn't occur when overwriting files on FAT32 drives.