package Adapter;

public class VlcPlayer implements AdvancedMediaPlayer{

  @Override
  public void playVLC( String fileName) {
  System.out.println("Playing vlc file. Name: "+ fileName);

  }

  @Override
  public void playMP4( String fileName) {
    
  }
  
}
