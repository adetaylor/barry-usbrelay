<? include ("barry.inc"); ?>

<? createHeader("Syncing your BlackBerry with Evolution"); ?>

<? createSubHeader("Introduction"); ?>

<p>This document describes the steps needed to sync your Blackberry with
Evolution, using OpenSync version 0.22 and the command line tool
msynctool.  The concepts are similar with other Opensync plugins,
and should be relatively straightforward to sync with other data sources.</p>


<? createSubHeader("Overview"); ?>

<p>The first sync requires the following steps:
<ul>
	<li>Run Evolution and make sure it has created its local databases</li>
	<li>Create a sync group with msynctool, and configure each member</li>
	<li>Shutdown Evolution servers</li>
	<li>Run the sync</li>
</ul>
</p>

<p>Future syncs only require the following steps:
<ul>
	<li>Shutdown Evolution servers</li>
	<li>Run the sync</li>
</ul>
</p>


<? createSubHeader("First Step"); ?>

<p>First step is to always make a backup of your data.  Use the GUI
backup tool that comes with Barry, or the RIM Windows Desktop software,
to make backups of your device data.</p>

<p>Remember that your device data is not the only database being operated
on.  Your Evolution data is also at risk, should something go wrong.
You should backup your Evolution data as well.
See
"<a href="http://ubuntu.wordpress.com/2005/12/03/how-to-backup-evolution/">How To Backup Evolution</a>" (external link)
for step by step instructions on backing up your local Evolution data.</p>


<? createSubHeader("Preparing Evolution"); ?>

<p>If you've never run Evolution before, start Evolution and follow its
initial configuration dialogs.  Once it is running, click on each of the
available section buttons.  These buttons include: Mail, Contacts,
Calendars, Memos, and Tasks.  Clicking on each of these, causes Evolution
to open and create the matching databases.</p>

<p>Each of these sections should have a "Personal" folder.  This is
where data from your Blackberry will end up, and any data in these
databases will be synced to your Blackberry as well.</p>

<p><b>Note:</b> Only Contacts and Calendar items are currently supported
in the Barry Opensync 0.22 plugin.</p>


<? createSubHeader("Preparing OpenSync"); ?>

<p>Opensync organizes its sync configurations in the form of groups.  Each
group contains two or more member plugins that will be synchronized.</p>

<p>For example, using msynctool, you can create a group called EvoBarry
which will sync your Blackberry and Evolution like this:</p>

<pre>
	msynctool --delgroup EvoBarry
	msynctool --addgroup EvoBarry
	msynctool --addmember EvoBarry evo2-sync
	msynctool --addmember EvoBarry barry-sync
	msynctool --configure EvoBarry 1
	msynctool --configure EvoBarry 2
	msynctool --showgroup EvoBarry
</pre>

<p>Each configuration stage (1 and 2) will open an editor, where you can
edit the member plugin's configuration file.  Evolution's plugin takes
its configuration in the form of XML.  For example:</p>

<pre>
	&lt;config&gt;
	   &lt;address_path&gt;file:///home/cdfrey/.evolution/addressbook/local/system&lt;/address_path&gt;
	   &lt;calendar_path&gt;file:///home/cdfrey/.evolution/calendar/local/system&lt;/calendar_path&gt;
	   &lt;tasks_path&gt;file:///home/cdfrey/.evolution/tasks/local/system&lt;/tasks_path&gt;
	&lt;config&gt;
</pre>

<p>Barry's plugin member takes a simple text file.  The default configuration
that comes with Barry is shown below:</p>

<pre>
	#
	# This is the default configuration file for the barry-sync opensync plugin.
	# Comments are preceded by a '#' mark at the beginning of a line.
	# The config format is a set of lines of <keyword> <values>.
	#
	# Keywords available:
	#
	# DebugMode        - If present, verbose USB debug output will be enabled
	#
	# Device           - If present, it is followed by the following values:
	#      PIN number    - PIN number of the device to sync with (in hex)
	#      sync calendar - 1 to sync calendar, 0 to skip
	#      sync contacts - 1 to sync contacts, 0 to skip
	#
	# Password secret  - If present, specifies the device's password in plaintext
	#

	#DebugMode

	Device 3009efe3 1 1

	#Password secret
</pre>

<p>Edit the device's PIN number, and save.  You're now ready to run your
first sync.</p>


<? createSubHeader("Syncing!"); ?>

<p>It is recommended that Evolution's backend servers be shutdown before
the sync is performed.  Therefore, make sure you've closed Evolution,
and run the following commands to sync, using the group you just configured:</p>

<pre>
	evolution --force-shutdown
	msynctool --sync EvoBarry
</pre>

<p>Status messages will appear at each stage of the sync: each plugin
fetches new records, the conflict resolution is performed by the Opensync
engine, and new records are written to each plugin.</p>


<? createSubHeader("Troubleshooting"); ?>

<p>There are a number of things that can go wrong during a sync:
<ul>
	<li>One of the plugins may crash</li>
	<li>Opensync may hang, or take a long time, while processing conflicts</li>
	<li>Opensync may get confused and duplicate a lot of data</li>
</ul>
</p>

<p><b>If one of the plugins crash...</b></p>

<p>If one of the plugins crashes due to a segmentation fault, try to get
a sequence of steps that can reproduce the crash every time.  At that
point, enable core dumps, and run it again:</p>

<pre>
	ulimit -c unlimited
	msynctool --sync EvoBarry
</pre>

<p>This will leave a core file somewhere on your filesystem.  In order
to get a useful backtrace from it, you will need the debug packages
for Barry and OpenSync.  The debug packages for Barry are available
at the
<a href="http://sourceforge.net/project/showfiles.php?group_id=153722">Sourceforge download page</a>.
Debug packages for OpenSync should
come with your distribution.</p>

<p>Once you have installed the matching debug packages, open the core
dump file like this, which will tell you which program was running when
the plugin crashed:</p>

<pre>
	gdb /bin/ls corefile
	[... lots of output ...]
	(gdb) quit
</pre>

<p>As gdb loads, it will print the name of the program that crashed.
Often this is /usr/lib/opensync/osplugin or something similar.
Load gdb again with the correct program, and use the backtrace (bt)
command:</p>

<pre>
	gdb /usr/lib/opensync/osplugin corefile
	[... lots of output ...]
	(gdb) bt
	[... useful output ...]
	(gdb) quit
</pre>

<p>Paste the "useful ouput" above into an email and
<?createLink("contact", "send it to us"); ?>.</p>



<p><b>If OpenSync hangs...</b></p>

<p>If the hang lasts only for about 30 seconds, then it is likely the
USB conversation that is timing out.  Enable the <b>DebugMode</b>
keyword in the Barry plugin configuration above, and send the last
few screens of output to the
<?createLink("contact", "mailing list"); ?>.</p>

<p>Otherwise, Opensync supports a detailed level of logging.  If you set
the environment variable <b>OSYNC_TRACE</b> to the path of an empty
directory, Opensync will write detailed logs for every thread
used during the syncing process.  These logs quickly get out of
hand, so delete them before each test run.</p>

<p>Some of these logs may contain private data, so before posting
them on the mailing list, or on a website, you may wish to
double check.  You can also
<?createLink("contact", "email them privately"); ?>
to the lead developer.</p>


<p><b>If you get a load of duplicates...</b></p>

<p>If the sync has crashed, note that OpenSync will know this and attempt
a slow-sync automatically the next time you run the sync.  If there is
a mismatch in supported fields, this can cause duplicates to be created
on one or possibly both sides of the sync.  For example, if your desktop
software supports a Speed field, which the Blackberry does not, then
with OpenSync 0.22, these records will look different, and duplicates will
be created.</p>

<p>This bug should be <a href="http://www.opensync.org/ticket/636">fixed
in the upcoming OpenSync 0.40.</a></p>

<p>In the meantime, it is much better to avoid slow-syncing, and re-create
your sync configuration from scratch, as documented above.</p>

<p>If you know that one side is authoritative (for example, you may know
that your Blackberry has the most up to date set of data), delete all
the data from the opposite data source, reconfigure, and sync again.</p>

<p>If all else fails, restore your backups and start fresh.</p>

