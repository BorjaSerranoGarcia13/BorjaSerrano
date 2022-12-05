using UnityEngine;

public class VolumeValueChange : MonoBehaviour {

    // Reference to Audio Source component
    private AudioSource audioSrc;

    // Music volume variable that will be modified
    // by dragging slider knob
    private float musicVolume = 1f;

    PlayerDead script2;

    finishLevel script;

	// Use this for initialization
  	void Start () {

          // Assign Audio Source component to control it
          audioSrc = GetComponent<AudioSource>();

          script2 = GameObject.Find("Player").GetComponent<PlayerDead>();

          script = GameObject.Find("End (Idle)").GetComponent<finishLevel>();
  	}

  	// Update is called once per frame
  	void Update () {

          // Setting volume option of Audio Source to be equal to musicVolume
          audioSrc.volume = musicVolume;

          if (script2.player_dead || script.levelDone)
          {
            musicVolume = 0.0f;
          }
  	}

    public void SetVolume(float vol)
    {
        musicVolume = vol;
         AudioListener.volume = vol;
    }
}
