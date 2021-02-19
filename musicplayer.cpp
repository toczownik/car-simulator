#include "musicplayer.h"

#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QGridLayout>
#include <QProgressBar>
#include <QPushButton>
#include <QSlider>
#include <QLabel>

MusicPlayer::MusicPlayer(QWidget *parent) : QWidget(parent)
{
    auto layout = new QGridLayout(this);
    setLayout(layout);

    auto playlist = new QMediaPlaylist();
    playlist->addMedia(QUrl::fromLocalFile(":/music/Despacito.mp3"));
    playlist->setPlaybackMode(QMediaPlaylist::Loop);
    auto player = new QMediaPlayer(this);
    player->setPlaylist(playlist);
    player->stop();

    auto songProgress = new QProgressBar(this);
    songProgress->setOrientation(Qt::Horizontal);
    songProgress->setTextVisible(true);
    songProgress->setStyleSheet("::chunk{background-color:red}");
    songProgress->setRange(0, 100);
    songProgress->setValue(40);
    layout->addWidget(songProgress, 2, 0, 2, 2);

    auto playButton = new QPushButton(this);
    playButton->setText("PLAY");
    connect(playButton, &QPushButton::clicked, player, &QMediaPlayer::play);
    layout->addWidget(playButton, 0, 0);

    auto pauseButton = new QPushButton(this);
    pauseButton->setText("PAUSE");
    connect(pauseButton, &QPushButton::clicked, player, &QMediaPlayer::pause);
    layout->addWidget(pauseButton, 0, 1);

    auto volumeSlider = new QSlider(this);
    volumeSlider->setOrientation(Qt::Horizontal);
    volumeSlider->setRange(0, 10);
    volumeSlider->setTickInterval(QSlider::NoTicks);
    connect(volumeSlider, &QSlider::valueChanged, player, &QMediaPlayer::setVolume);
    layout->addWidget(volumeSlider, 1, 1, 1, 2);
    auto volumeSliderLabel = new QLabel(volumeSlider);
    volumeSliderLabel->setText("SET VOLUME");
    layout->addWidget(volumeSliderLabel, 1, 0);
}
