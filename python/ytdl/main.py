from pytube import YouTube

def on_complete(stream, file_path):
   print(file_path)
   print("Done")

def on_progress(stream, chunk, bytes_remaining):
   print(100 - (bytes_remaining / stream.filesize * 100))

def main():
   link = "https://www.youtube.com/watch?v=NtzDjNhPZgU"
   link = "https://www.youtube.com/watch?v=YNOu2oGBFFM"
   link = "https://www.youtube.com/watch?v=2-aWEYezEMk"

   video_object = YouTube(link,
      on_complete_callback=on_complete,
      on_progress_callback=on_progress)
   print(f"Title:        {video_object.title}")
   print(f"Length:       {round(video_object.length / 60, 2)} minutes")
   if video_object.views > 1_000_000:
      print(f"Views:        {video_object.views / 1_000_000} million")
   else:
      print(f"Views:        {video_object.views}")
   print(f"Author:       {video_object.author}")
   # print(f"Description: {video_object.description}")
   print(f"Publish Date: {video_object.publish_date}")
   print(f"Keywords: {video_object.keywords}")
   #print(f"Rating: {video_object.rating}")

   #for stream in video_object.streams:
   #   print(stream)

   #best = video_object.streams.get_highest_resolution()
   worst = video_object.streams.get_lowest_resolution()
   #audio = video_object.streams.get_audio_only()

   # download
   print("Downloading")

   worst.download("./videos")

   print("End")

if __name__ == "__main__":
   main()

