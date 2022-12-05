using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

public class scoreCounter : MonoBehaviour
{
    public float scorePlayer1 = 0f;
    public float scorePlayer2 = 0f;

    public ParticleSystem system1;
    public ParticleSystem system2;
    public ParticleSystem system3;
    public ParticleSystem system4;
    public ParticleSystem system5;
    public ParticleSystem system6;
    public ParticleSystem system7;
    public ParticleSystem system8;
    public ParticleSystem system9;
    public ParticleSystem system10;

    public AudioSource Sound;
    public AudioSource Sound2;

    public Text player1Text;
    public Text player2Text;

    public bool movActive;

    public bool goalActive;

  // Start is called before the first frame update
  void Start()
  {
    player1Text.color = Color.red;
    player2Text.color = Color.blue;

    movActive = true;
  }

  IEnumerator FireWorks()
  {
      Sound.Play(0);
      Sound2.Play(0);

      movActive = false;

      timeCounter a = GameObject.Find("ScoreManager").GetComponent<timeCounter>();
      a.GameIsPaused = true;

      yield return new WaitForSeconds(0.3f);

      system1.Play();
      system10.Play();
      yield return new WaitForSeconds(0.3f);

      system2.Play();
      system9.Play();
      yield return new WaitForSeconds(0.3f);

      system3.Play();
      system8.Play();
      yield return new WaitForSeconds(0.3f);

      system4.Play();
      system7.Play();
      yield return new WaitForSeconds(0.3f);

      system5.Play();
      system6.Play();
      yield return new WaitForSeconds(1.5f);

      movActive = true;
    }

    void Update()
    {
      player1Text.text = scorePlayer1.ToString("0");
      player2Text.text = scorePlayer2.ToString("0");
    }

    public void StartFire()
    {
        StartCoroutine(FireWorks());
    }

    public void Maps()
    {
      SceneManager.LoadScene(0);
    }

    public void Retry()
    {
      Scene scene = SceneManager.GetActiveScene(); SceneManager.LoadScene(scene.name);
    }
}
