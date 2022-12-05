using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PuntuationController : MonoBehaviour {

    public delegate void PuntuationTaken(int puntuation);
    public event PuntuationTaken OnPuntuationTaken;

    [SerializeField]
    private int puntuation;

    public void TakePuntuation(int puntuation) {
        this.puntuation += puntuation;
        if (OnPuntuationTaken != null) {
            OnPuntuationTaken(this.puntuation);
        }
    }

    public int GetPuntuation() {
        return puntuation;
    }
}
