package Adapter;

public class MediaAdapter implements MediaPlayerInterface {

  AdvancedMediaPlayer advancedMusicPlayer;

  MediaAdapter(String audioType){
    if(audioType.equalsIgnoreCase("vlc") ){
      advancedMusicPlayer = new VlcPlayer();
    } else if (audioType.equalsIgnoreCase("mp4")){
      advancedMusicPlayer = new Mp4Player();
    }
  }

  @Override
  public void play(String audioType, String fileName) {
    if(audioType.equalsIgnoreCase("mp4")){
      advancedMusicPlayer.playMP4(fileName);
    }
    else if(audioType.equalsIgnoreCase("vlc")){
      advancedMusicPlayer.playVLC(fileName);
    }
  }
  
}
