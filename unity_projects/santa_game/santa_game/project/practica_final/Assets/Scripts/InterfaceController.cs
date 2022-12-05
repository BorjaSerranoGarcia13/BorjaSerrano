using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class InterfaceController : MonoBehaviour {

    public Text lifeText;
    public Text distanceText;
    public Text puntuationText;

    public GameObject player;

    void Start() {
        if (distanceText != null) {
            distanceText.text = "Distance: 0";
            player.GetComponent<PlayerInfiniteStageController>().OnPlayerDistanceWalked += OnPlayerDistanceWalkedHandler;
        }

        if (puntuationText != null) {
            puntuationText.text = "Puntuation: 0";
            player.GetComponent<PuntuationController>().OnPuntuationTaken += OnPuntuationTakenHandler;
        }

        lifeText.text = "Lifes: " + player.GetComponent<LifeController>().GetLife();
        player.GetComponent<LifeController>().OnDamageTaken += OnDamageTakenHandler;
    }

    void OnDisabled() {
        player.GetComponent<LifeController>().OnDamageTaken -= OnDamageTakenHandler;

        if (distanceText != null) {
            player.GetComponent<PlayerInfiniteStageController>().OnPlayerDistanceWalked -= OnPlayerDistanceWalkedHandler;
        }

        if (puntuationText != null) {
            player.GetComponent<PuntuationController>().OnPuntuationTaken -= OnPuntuationTakenHandler;
        }

    }

    void OnEnabled() {
        player.GetComponent<LifeController>().OnDamageTaken += OnDamageTakenHandler;

        if (distanceText != null) {
            player.GetComponent<PlayerInfiniteStageController>().OnPlayerDistanceWalked += OnPlayerDistanceWalkedHandler;
        }

        if (puntuationText != null) {
            player.GetComponent<PuntuationController>().OnPuntuationTaken += OnPuntuationTakenHandler;
        }
    }

    void OnDamageTakenHandler(int life, int damage) {
        lifeText.text = "Lifes: " + life;
    }

    void OnPlayerDistanceWalkedHandler(float distance) {
        distanceText.text = "Distance: " + Mathf.Floor(distance);
    }

    void OnPuntuationTakenHandler(int puntuation) {
        puntuationText.text = "Puntuarion: " + puntuation;
    }
}
