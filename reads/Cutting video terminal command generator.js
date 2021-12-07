var video_length = 359; // in seconds.
var snippet_interval = 30; // 300 = every 5 minutes, 180 = every 3 minutes
var snippet_length = 7;

commands = "";

for (var i = 0; ( i + snippet_interval + snippet_length ) < video_length; i += snippet_interval) {

	// Seconds to HH-MM-SS, as seen on https://stackoverflow.com/a/25279340
	start_cut = new Date(i * 1000).toISOString().substr(11, 8);
	end_cut  = new Date( snippet_length * 1000).toISOString().substr(11, 8);

	// ffmpeg -ss 00:01:00 -i input.mp4 -to 00:01:30 -c copy output.mp4
	commands += "ffmpeg -ss " + start_cut + " -i input.mp4 -to " + end_cut + " -c copy output" + i + ".mp4";

	commands += "\n";
}

console.log(commands);
