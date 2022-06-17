import os
import json
import time
import math
import sys
import numpy as np
import matplotlib.pyplot as plt
from core.data_processor import DataLoader
from core.model import Model


def eprint(*args, **kwargs):
    print(*args, file=sys.stderr, **kwargs)

def plot_results(predicted_data, true_data):
    fig = plt.figure(facecolor='white')
    ax = fig.add_subplot(111)
    ax.plot(true_data, label='True Data')
    plt.plot(predicted_data, label='Prediction')
    plt.legend()
    plt.savefig('series.png')
    # plt.show()


def plot_results_multiple(predicted_data, true_data, prediction_len):
    fig = plt.figure(facecolor='white')
    ax = fig.add_subplot(111)
    ax.plot(true_data, label='True Data')
	# Pad the list of predictions to shift it in the graph to it's correct start
    for i, data in enumerate(predicted_data):
        padding = [None for p in range(i * prediction_len)]
        plt.plot(padding + data, label='Prediction')
        plt.legend()
    plt.show()


class LSTMAnomaly:
    def __init__(self):
        # import sys 
        # stdoutOrigin=sys.stdout 
        # sys.stdout = open("log.txt", "w")
        # sys.stderr = open("log_err.txt", "w")
        eprint("call INIT")


    def setup(self):
        eprint("call setup")

    def predict(self):

        eprint("call predict")
        configs = json.load(open('config_new.json', 'r'))
        if not os.path.exists(configs['model']['save_dir']): os.makedirs(configs['model']['save_dir'])

        data = DataLoader(
            os.path.join('data', configs['data']['filename']),
            os.path.join('data', configs['data']['filename_test']),
            configs['data']['train_test_split'],
            configs['data']['columns']
        )

        model = Model()
        model.build_model(configs)
        x, y = data.get_train_data(
            seq_len=configs['data']['sequence_length'],
            normalise=configs['data']['normalise']
        )
        model.load_model('longlong.h5')

        x_test, y_test = data.get_test_data(
            seq_len=configs['data']['sequence_length'],
            normalise=configs['data']['normalise']
        )
     
        predictions = model.predict_point_by_point(x_test)
        std = np.std(y_test, ddof=1)
        diff0 = (predictions[0]-y_test[0])[0]

        print('std = ', std)
        print('diff = ', diff0)

        for i, _ in enumerate(predictions):
            predictions[i] = predictions[i]-diff0

        #anomaly detection
        anomal = 0
        for i, _ in enumerate(predictions):
            d = math.sqrt((predictions[i] - y_test[i])[0] * (predictions[i] - y_test[i])[0])
            if d > 2*std:
                print('Anomaly at ', i)
                anomal = anomal + 1
                diff = (predictions[i]-y_test[i])[0]
                for j, _ in enumerate(predictions): 
                    if j>=i:
                        predictions[j] = predictions[j]-diff

        plot_results(predictions, y_test)
        # return anomal

def main():
    ano = LSTMAnomaly()
    ano.setup()

    ano.predict()


if __name__ == '__main__':
    main()
 