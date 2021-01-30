''' Performance_Metrics module

Module contains functions to calculate metrics based on the performance of a model 
'''
import seaborn as sns

from matplotlib import pyplot as plt
from numpy import sqrt, argmax
from sklearn import metrics
from sklearn.metrics import classification_report, precision_recall_fscore_support, roc_curve, RocCurveDisplay

''' Calculates metrics: precision, fscore, sensitivity, specificity'''
def calculate_metrics(validations, predictions):
    # ignores recoil and data
    precision, _, fscore, _ = precision_recall_fscore_support(validations, predictions,  average='weighted')
    mcm = metrics.multilabel_confusion_matrix(validations, predictions)

    TN = mcm[:, 0, 0]
    TP = mcm[:, 1, 1]
    FN = mcm[:, 1, 0]
    FP = mcm[:, 0, 1]

    sensitivity = TP/(TP+FN)
    specificity = TN/(TN+FP)

    return precision, fscore, sensitivity, specificity

''' Calcuates the optimal threasholds using the ROC curves '''
def calculate_optimal_thresholds(validations, predictions):
    optimal_thresholds = [0, 0, 0, 0]

    for i in range(len(optimal_thresholds)):
        FP_rates, TP_rates, thresholds = roc_curve(validations[:, i], predictions[:, i])
        gmeans = sqrt(TP_rates * (1-FP_rates))
        ix = argmax(gmeans)
        optimal_thresholds[i] = thresholds[argmax(gmeans)]
    
    return optimal_thresholds

''' Creates a heatmap of True Label vs Predicted Labels '''
def plot_confusion_matrix(validations, predictions):
    matrix = metrics.confusion_matrix(validations, predictions)
    plt.figure(figsize=(4, 4))
    LABELS = ["1","2","3","4"]
    sns.heatmap(matrix, cmap="coolwarm", linecolor='white', linewidths=1,
                xticklabels=LABELS, yticklabels=LABELS, annot=True, fmt="d")
    plt.title("Confusion Matrix")
    plt.ylabel("True Label")
    plt.xlabel("Predicted Label")
    plt.show()

''' Generates a figure with ROC curve and evaluates the most optimal thresholds '''
def plot_roc_curve(validations, predictions):
    for i in range(predictions.shape[1]):
        FP_rates, TP_rates, thresholds = roc_curve(validations[:, i], predictions[:, i])
        roc_auc = metrics.auc(FP_rates, TP_rates)
        display = metrics.RocCurveDisplay(fpr=FP_rates, tpr=TP_rates, roc_auc=roc_auc, estimator_name='example estimator')
        display.plot()
        plt.show()       



